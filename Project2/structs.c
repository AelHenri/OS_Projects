#include "structs.h"

struct t_message {
	char *data;
	t_process *subscribers;
	t_message *next;
};

struct t_process {
	int pid;
	t_process *next;
};

struct topic {
	int t_id;
	int nb_msg;
	t_message *mlist;
	t_process *subscribers;
	t_process *publishers;
	topic *next;
};