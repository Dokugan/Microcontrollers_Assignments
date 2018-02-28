/*
 * fsm.c
 *
 * Created: 2-2-2018 14:49:31
 * Author : stijn
 */ 
#include <avr/io.h>
#include <stdarg.h>

typedef enum{
	Start, S1, S2, S3, End
}STATES;
typedef void (*parallel_func)();

parallel_func* funcs_to_run; 
void** fun_args;
int funcs_size = 0;
int thread_avaiable = 1;

void sys_loop(){
	while(1){
		
	}
}

void add_parallel_func(parallel_func func, void* args[]){
	funcs_to_run[funcs_size] = func;
	fun_args[funcs_size] = args;
	funcs_size ++;
}

void start_queue_cycle(){
	
}

void interupt(){
	
}

void handle_input(int btn_num){
	
}

void check_input_parallel(void (*on_input)(int), int listen_port){
	int i;
	int input;
	while(1){
		if (listen_port != 0x00)
		{
			input = listen_port;
			for (i = 0; i < 8; i++)
			{
				if (input >> i & 0x01)
				{
					on_input(i);
				}
			}
		}
		interupt();
	}
}

void handleState(STATES state){
	
}

int main(void)
{
	DDRC = 0x00;
	DDRD = 0xFF;
	int out = PINC;
	void* args[2] = {&handle_input, &out};
	
	add_parallel_func(&check_input_parallel, args);
}

