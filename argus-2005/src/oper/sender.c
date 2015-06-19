#include <argus.h>

struct display
{
	operator_t opr;
	char *buf;
};

int display_receive (struct display *opr, int type, tuple_t *tup)
{
	printf("TUPLE-%d\n", type);
	tuple_unlock(tup);
	return 0;
}

int display_destroy (struct display *opr)
{
	free(opr->buf);
	free(opr);
	return 0;
}

operator_t *display_create (char *buf)
{
	struct display *disp;
	disp = type_alloc(struct display);
	disp->opr.receive = (operator_receive_f)display_receive;
	disp->opr.destroy = (operator_destroy_f)display_destroy;
	disp->buf = strdup(buf);
	return (operator_t *)disp;
}

struct sender
{
	operator_t opr;
	argus_callback_f callback;
	void *param;
};

int sender_receive (struct sender *opr, int type, tuple_t *tup)
{
	opr->callback(opr->param, ARGUS_TUPLE, type, tup);	
	return 0;
}

int sender_destroy (struct sender *opr)
{
	free(opr);
	return 0;
}

operator_t *sender_create (argus_callback_f callback, void *param)
{
	struct sender *disp;
	disp = type_alloc(struct sender);
	disp->opr.receive = (operator_receive_f)sender_receive;
	disp->opr.destroy = (operator_destroy_f)sender_destroy;
	disp->callback = callback;
	disp->param = param;
	return (operator_t *)disp;
}

