all:lotApp

OBJS:= user.o admin.o interfaceUI.o list.o public.o
LOTAPP_OBJS:=lotApp.o $(OBJS)

lotApp:$(OBJS)
	gcc $(OBJS) -o lotApp -Wall

%.o:%.c
	gcc -c $< -o $@ -Wall

clean:
	rm -fr lotApp
	rm -fr $(OBJS)