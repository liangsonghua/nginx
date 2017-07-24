
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_EVENT_PIPE_H_INCLUDED_
#define _NGX_EVENT_PIPE_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>


typedef struct ngx_event_pipe_s  ngx_event_pipe_t;

typedef ngx_int_t (*ngx_event_pipe_input_filter_pt)(ngx_event_pipe_t *p,
                                                    ngx_buf_t *buf);
typedef ngx_int_t (*ngx_event_pipe_output_filter_pt)(void *data,
                                                     ngx_chain_t *chain);


struct ngx_event_pipe_s {
    ngx_connection_t  *upstream;//nginx与上游服务器的连接
    ngx_connection_t  *downstream;//nginx与下游服务器的连接

    ngx_chain_t       *free_raw_bufs;//直接接收自上游服务器的缓冲区链表
    ngx_chain_t       *in;//表示接收到的上游响应缓冲区
    ngx_chain_t      **last_in;//指向刚刚接收到的一个缓冲区

    ngx_chain_t       *writing;

    ngx_chain_t       *out;
    ngx_chain_t       *free;//等待释放的缓冲区
    ngx_chain_t       *busy;//还没有发送完的缓冲区链表

    /*
     * the input filter i.e. that moves HTTP/1.1 chunks
     * from the raw bufs to an incoming chain
     */

    ngx_event_pipe_input_filter_pt    input_filter;//处理来自上游服务器的缓冲区
    void                             *input_ctx;//一般设置为ngx_http_request_t结构体的地址

    ngx_event_pipe_output_filter_pt   output_filter;//表示向下游发送响应的方法
    void                             *output_ctx;

#if (NGX_THREADS || NGX_COMPAT)
    ngx_int_t                       (*thread_handler)(ngx_thread_task_t *task,
                                                      ngx_file_t *file);
    void                             *thread_ctx;
    ngx_thread_task_t                *thread_task;
#endif

    unsigned           read:1;//为一表示已经接收到上游的响应
    unsigned           cacheable:1;//启用文件缓存
    unsigned           single_buf:1;//为一时表示一次只能接收一个ngx_buf_t缓冲区
    unsigned           free_bufs:1;//为一时表示一旦不再接收上游响应包体尽快释放
    unsigned           upstream_done:1;//上游间的交互已经结束
    unsigned           upstream_error:1;
    unsigned           upstream_eof:1;//连接状态
    unsigned           upstream_blocked:1;//需要暂停读取上游响应，需要通过向下游发送响应来清理缓冲区
    unsigned           downstream_done:1;
    unsigned           downstream_error:1;
    unsigned           cyclic_temp_file:1;//试图利用缓冲文件
    unsigned           aio:1;

    ngx_int_t          allocated;//目前分配的缓冲区数目
    ngx_bufs_t         bufs;//接收上游响应的内存缓冲区大小
    ngx_buf_tag_t      tag;

    ssize_t            busy_size;//设置Busy缓冲区中待发送的响应长度。必须等待busy缓冲区发送了足够的内容，才能继续发送out和in缓冲区的内容

    off_t              read_length;//上游响应包体的长度
    off_t              length;

    off_t              max_temp_file_size;
    ssize_t            temp_file_write_size;

    ngx_msec_t         read_timeout;
    ngx_msec_t         send_timeout;
    ssize_t            send_lowat;

    ngx_pool_t        *pool;
    ngx_log_t         *log;

    ngx_chain_t       *preread_bufs;//表示在接收上游服务器响应头部阶段，已经读取到的响应包体
    size_t             preread_size;
    ngx_buf_t         *buf_to_file;

    size_t             limit_rate;
    time_t             start_sec;

    ngx_temp_file_t   *temp_file;//存放上游响应的临时文件

    /* STUB */ int     num;
};


ngx_int_t ngx_event_pipe(ngx_event_pipe_t *p, ngx_int_t do_write);
ngx_int_t ngx_event_pipe_copy_input_filter(ngx_event_pipe_t *p, ngx_buf_t *buf);
ngx_int_t ngx_event_pipe_add_free_buf(ngx_event_pipe_t *p, ngx_buf_t *b);


#endif /* _NGX_EVENT_PIPE_H_INCLUDED_ */
