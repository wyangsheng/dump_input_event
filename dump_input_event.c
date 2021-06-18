/* dump_input_event.c
 * 
 * dump linux input event
 * 
 * author: Yangsheng Wang
 * wang_yangsheng@163.com
 * 
 * coding in 2021/6/19
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>

#if 0
struct input_event {
	struct timeval time;
	__u16 type;
	__u16 code;
	__s32 value;
};

struct timeval {
	__kernel_time_t		tv_sec;		/* seconds */
	__kernel_suseconds_t	tv_usec;	/* microseconds */
};

/* 
 * include/linux/input-event-codes.h
 *
 * Event types
 */

#define EV_SYN			0x00
#define EV_KEY			0x01
#define EV_REL			0x02
#define EV_ABS			0x03
#define EV_MSC			0x04
#define EV_SW			0x05
#define EV_LED			0x11
#define EV_SND			0x12
#define EV_REP			0x14
#define EV_FF			0x15
#define EV_PWR			0x16
#define EV_FF_STATUS		0x17
#define EV_MAX			0x1f
#define EV_CNT			(EV_MAX+1)
#endif

int main(int argc, char *argv[])
{
	struct input_event event;
	int input_fd;
	int i;
	int ret;
	struct tm *t;

	if (argc != 2) {
		printf("%s [/dev/input/event*]\n", argv[0]);
		return -1;
	}
	printf("input device:%s\n", argv[1]);

	printf("sizeof(struct input_event):%d\n", sizeof(event));

	input_fd = open(argv[1], O_RDWR);
	if (input_fd < 0) {
		printf("open() %s failed\n", argv[1]);
		return -1;
	}

	while (1) {
		ret = read(input_fd, &event, sizeof(event));
		if (ret < 0) {
			printf("read() failed\n");
			close(input_fd);
			return -1;
		}
		t = localtime(&event.time.tv_sec);
		/* printf("tv_sec:%u tv_usec:%u, key type:0x%x code:0x%x value:0x%x\n", 
			event.time.tv_sec, event.time.tv_usec,
			event.type, event.code, event.value);*/

		printf("%d-%d-%d ", t->tm_year+1900, t->tm_mon+1, t->tm_mday);
		printf("%d:%d:%d ", t->tm_hour, t->tm_min, t->tm_sec);
		printf("%u(us) ", event.time.tv_usec);
		printf("key type:0x%x code:0x%x value:0x%x\n", 
			event.type, event.code, event.value);

		if (event.type == EV_SYN)
			printf("\n");
	}

	close(input_fd);

	return 0;
}
