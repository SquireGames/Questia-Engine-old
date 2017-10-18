##common cmake helper functions

##debugging:

#prints the varible name and it's value
MACRO(PRINT var)
	MESSAGE(STATUS "${var}: " ${${var}})
ENDMACRO()
