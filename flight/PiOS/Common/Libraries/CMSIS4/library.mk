#
# Rules to add CMSIS4 to a PiOS target
#

CMSIS4_DIR		:=	$(dir $(lastword $(MAKEFILE_LIST)))
EXTRAINCDIRS		+=	$(CMSIS4_DIR)/Include
