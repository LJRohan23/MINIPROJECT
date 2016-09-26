#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#define BUFSIZE 1024
typedef struct node {
	char ch;
	struct node *next;
}node;
typedef struct queue {
	node * front, *rear;
}queue;
enum FLAGS {
	_READ;
	_WRITE;
	_RDWR;
	_EOF;
	_ERR;
}
// change the queue functions
void qinit(queue *q) {
	q->front = NULL;
}
int qempty(queue *q) {
	return (q->front == NULL);
}
int qfull(queue *q) {
	return 0;
}
char dequeue(queue*q) {
	node *t =NULL;
	t = q->front;
	q->front = q->front ->next;
	char c = t->ch;
	free(t);
	return c;
}
void enqueue(queue*q, char c) {
	node *t = (char*)malloc(sizeof(char));
	t->ch = c;
	note * temp = q->front;
	for(; ; q->front = (q->front)->next) {
		if(q->front == NULL) {
			break;
		}
		else
		if(q->front->next == NULL) {
			break;
		}
	}
	if(q->front == NULL) {
		q->front = t;
	}
	else {
		q->front->next = t;
		q->front = t;
	}
	q->front = temp;
}
typedef struct files {
	int count_r;
	char *ptr;
	char *base;
	queue q1;
	int cnt;
	int fd;
	int mode;
	char *name;
}files;
int fillbuffer(files *fp) {
	if(fp->mode != _READ || fp->mode != _WRITE || fp->mode != _RDWR ) {
		return EOF;
	}
	if(fp-> base == NULL) { //currently unbuffered
		fp->base = (char *)malloc(BUFSIZE);
		if(fp->base  == NULL) {
			return EOF;
	}
	fp->ptr = f->base;//resetting the buffer position
	fp->cnt = read(fp->fd, fp->base, BUFSIZE);
	if(--fp->cnt < 0) {
		if(fp->cnt == -1) {
			fp->mode = _EOF;
		}
		else
			fp->flag = _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) (*(fp->ptr)++);
}
int fgetc(files *fp) {
	char ch;
	if(!empty(&fp->q1)) {
		ch = dequeue(&fp->q1);
		return (int)ch;
	}
	fp->total_r ++;
	if(--fp->cnt < 0 ) {
		if((x = fillbuffer(fp)) == EOF )
			return EOF;
	}
	return (int)fp->ptr++;
}
int ungetc(char ch, files *fp) {
	if(!qfull(&fp->q1)) {
		enqueue(&fp->q1, ch);
		/*if(fp->ptr != fp->base) {
			fp->ptr --;
		}*/
		return (int)ch;
	}
	return EOF;
}

