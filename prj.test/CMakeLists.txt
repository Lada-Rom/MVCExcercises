add_subdirectory(catch2_complex)
add_subdirectory(catch2_rational)
add_subdirectory(catch2_longint)
add_subdirectory(catch2_dynarray)
add_subdirectory(catch2_matrixa)
add_subdirectory(catch2_matrixl)
add_subdirectory(catch2_stackl)
add_subdirectory(catch2_queuea)

set_property(TARGET 
	catch2_complex 
	catch2_rational 
	catch2_longint 
	catch2_dynarray 
	catch2_matrixa 
	catch2_matrixl 
	catch2_queuea
	catch2_stackl PROPERTY CXX_STANDARD 17)

