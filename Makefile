##
## EPITECH PROJECT, 2021
## zappy
## File description:
## Makefile
##

zappy_server:
	@make -C server
	@cp server/zappy_server .

zappy_gui:
	@make -C gui
	@cp gui/zappy_gui .

zappy_ai:
	@make -C ai
	@cp ai/zappy_ai .

all:
	@zappy_server
	@zappy_gui
	@zappy_ai

clean:
	@make clean -C server
	@make clean -C gui
	@make clean -C ai

fclean:	clean
	@make fclean -C server
	@make fclean -C gui
	@make fclean -C ai
	@rm -f zappy_server
	@rm -f zappy_gui
	@rm -f zappy_ai

re:
	@make re -C server
	@cp server/zappy_server .
	@make re -C gui
	@cp gui/zappy_gui .
	@make re -C ai
	@cp ai/zappy_ai .

.PHONY:	all clean fclean re
