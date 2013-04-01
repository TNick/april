#! /usr/bin/python

#* ========================================================================= *#
#* ------------------------------------------------------------------------- *#
##
##  \file        tpl.py
##  \date        Jully 2011
##  \author        TNick
##
##  \brief        Script for generating files from templates
##
##
## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ @n
## Please read README and COPYING in root folder @n
## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ @n
##
#* ------------------------------------------------------------------------- *#
#* ========================================================================= *#
##
##
##
##
#*  INCLUDES    ------------------------------------------------------------ *#

import    fileinput, string, sys
import    os
from    time import gmtime, strftime

#*  INCLUDES    ============================================================ *#
##
##
##
##
#*  DATA    ---------------------------------------------------------------- *#

## used with templates to replace the ##AUTH## tag
g_s_auth = "TNick"


## the list of known templates

# 0 - String - Name
# 1 - String - Default location
# 2 - List -   Template files

g_data_list = [

    [ "C/C++ header (.h)",                   "../../april",            ["template.h"] ],
    [ "C/C++ source file (.cc)",             "../../april",            ["template.cc"] ],
    [ "C/C++ pair (.h and .cc)",             "../../april",            ["template.h", "template.cc"] ],
    [ "C/C++ class (.h and .cc)",            "../../april",            ["class_template.h", "class_template.cc"] ],
    [ "C/C++ manager class (.h and .cc)",    "../../april",            ["mgr_template.h", "mgr_template.cc"] ],
    [ "Qt main form (ui, .h and .cc)",       "../../april",            ["form_template.h", "form_template.cc", "form_template.ui"]  ],
    [ "Qt dialog (ui, .h and .cc)",          "../../april",            ["dlg_template.h", "dlg_template.cc", "dlg_template.ui"] ],
    [ "python file",                         "../../tools/python",     ["template.py"] ],

]

## number of templates that we know of
g_templ_count = len( g_data_list )


#*  DATA    ================================================================ *#
##
##
##
##
#*  FUNCTIONS    ----------------------------------------------------------- *#

#* ------------------------------------------------------------------------- *#
def    showLogo():
    """ Simply print an informative logo at the start of the program """

    print("===================================================")
    print("Utility for file creation based on template")
    print("===================================================")
    print("")

#* ========================================================================= *#

#* ------------------------------------------------------------------------- *#
def    generateTheFile(source_file, destination_file, base_name):
    """ Function that produces a new file from a template file

    The function shall attempt to read the template file in a string, replace
    known keywords by their respective values and write the output to a file
    """


    # input the text from file
    file = None
    try:
        file = open(source_file, "r")
        text = file.read()
        file.close()
        file = None
    except:
        print("Error!!! File " + source_file + " could not be readed!")
        if (file != None):
            file.close()
        return 1

    text = text.replace("##U_FILENAME##",base_name.upper())
    text = text.replace("##L_FILENAME##",base_name.lower())
    text = text.replace("##FILENAME##",base_name.lower())
    text = text.replace("##DATA##",strftime("%b %Y", gmtime()))
    text = text.replace("##NDAY##",strftime("%d", gmtime()))
    text = text.replace("##DAY##",strftime("%a", gmtime()))
    text = text.replace("##MONTH##",strftime("%b", gmtime()))
    text = text.replace("##YEAR##",strftime("%Y", gmtime()))
    text = text.replace("##HOUR##",strftime("%H", gmtime()))
    text = text.replace("##MINUTE##",strftime("%M", gmtime()))
    text = text.replace("##SECOND##",strftime("%S", gmtime()))
    text = text.replace("##CLASS##",base_name)
    text = text.replace("##AUTHOR##",g_s_auth)


    # output the result
    try:
        file = open(destination_file, "w")
        file.write(text)
        file.close()
        file = None
    except:
        print("Error!!! File " + destination_file + " could not be writed!")
        if (file != None):
            file.close()
        return 1

    print("File " + destination_file + " generated")
    return 0
#* ========================================================================= *#

#* ------------------------------------------------------------------------- *#
def    askName():
    """ the function asks the user for a name to be used

    This name is used both for file name(s) and for internal elements
    like guards, class name, ...
    """

    the_name = raw_input("The name: ")
    if (the_name == ""):
        print("  action was cancelled. Exiting...")
    return the_name
#* ========================================================================= *#

#* ------------------------------------------------------------------------- *#
def recFolders ( crt_path, level, max_level, out_list ):
    """ gets the list of folders with at most max_level depth """

    if ( level >= max_level ):
        return
    for l_it in os.listdir( crt_path ):
        full_path = crt_path + os.sep + l_it
        if ( l_it == ".svn" ):
            pass
        elif ( os.path.isdir( full_path ) ):
            out_list.append( full_path )
            recFolders( full_path, level+1, max_level, out_list )


#* ========================================================================= *#

#* ------------------------------------------------------------------------- *#
def    askOutPath(type_of_outp):
    """ the function asks the user for a path and returns that path

    Source folder shall be presented as a default and used when only RETURN
    is pressed
    """



    # following code is specific to the way I organise projects
    # project
    #   april
    #   tools
    #     python
    #     templ
    # with this file being run from python folder

    if   ( (type_of_outp < 0) or ( type_of_outp >= g_templ_count ) ):
        print("Error!!! Bogus input; type must be a value between 0 and " + str(g_templ_count-1) )
        return ""
    else:
        s_pth_rel = g_data_list[type_of_outp][1]


    s_pth_rel = os.path.abspath( s_pth_rel )
    print( "Destination shortcuts:" )

    dirs = []
    recFolders( s_pth_rel, 0, 3, dirs )
    i = 0
    for d in dirs:
        print( "[" + str( i ) + "] " + dirs[i][ len( s_pth_rel )+1 :] )
        i = i + 1

    the_name = raw_input("The destination path<" + s_pth_rel + ">: ")
    if (the_name == ""):
        return s_pth_rel
    else:
        try:
            i = int(the_name)
            the_name = dirs[i]
        except:
            pass

    return the_name
#* ========================================================================= *#

#* ------------------------------------------------------------------------- *#
def    askType():
    """ the function asks the user for template type

    For ease of use a number shall be presented. Valid options are:
    c/c++ header, c/c++ source, c/c++ header and source, c/c++ class
    python file
    """

    # infinite loop for bogus input from user
    while 1:
        print("Please select a template:")
        idx_ref = 0
        for tpl_e in g_data_list:
            print("  " + str(idx_ref) + " - " + tpl_e[0] )
            idx_ref = idx_ref + 1

        number = raw_input("Your selection (a number between 0 and " + str(g_templ_count-1) + "): ")
        if ( number == "Q" ):
            return 0
        if ( number == "q" ):
            return 0
        try:
            number = int(number)

            if   ( (number >= 0) and ( number < g_templ_count ) ):
                return number
        except:
            pass

        print("")
        print("Your selection is invalid. Try again, please!")
        print("(to cancel, press Q)")
        print("")

    return 0
#* ========================================================================= *#

#* ------------------------------------------------------------------------- *#
def    generateOutput(o_ty, o_loc, o_name):
    """ the function generates output based on path, template and type

    This is a high level function that may be used from outside.
    """

    # will hold the name of the template file to use
    s_tmpl_in = ""
    # the files that need to be generated

    # informative text before proceding to actual job
    s_out_inf = "Generating " + o_name + " "

    if   ( (o_ty >= 0) and ( o_ty < g_templ_count ) ):
        s_out_inf += g_data_list[o_ty][0]
        ls_out = g_data_list[o_ty][2]
    else:
        print("Error!!! Bogus input; type must be a value between 0 and " + str( g_templ_count-1 ) )
        return 1

    s_out_inf += " in:"
    print(s_out_inf)
    print(o_loc)


    # iterate in all entries from list; generate one file for each
    for s_file_src in ls_out:
        s_file_ext = os.path.splitext(s_file_src)[1]
        res = generateTheFile(
            os.path.join("../templ",s_file_src),
            os.path.join(o_loc,o_name.lower() + s_file_ext),
            o_name)
        if (res != 0):
            return res

    # we're good
    return 0
#* ========================================================================= *#

#* ------------------------------------------------------------------------- *#
def    main():
    """ Main function that is called when the module is loaded by itself

    The function shall ask the user for input, then will generate the file(s)
    """


    output_type = 0  # this shall hold the type of output that is to be gen.
    output_loc = ""  # this shall hold the location for output
    output_name = "" # this shall hold the name for output


    # present a simple logo
    showLogo()

    # ask for the type of output
    output_type = askType()
    if (output_type == 0):
        return 101

    # ask the user for a location
    output_loc = askOutPath(output_type)
    if (output_loc == ""):
        return 102

    # ask the user for a name
    output_name = askName()
    if (output_name == ""):
        return 103

    # finally generate the output
    return generateOutput(output_type, output_loc, output_name)
#* ========================================================================= *#

if __name__ == "__main__":
    sys.exit(main())

#*  FUNCTIONS    =========================================================== *#
##
##
##
##
#* ------------------------------------------------------------------------- *#
#* ========================================================================= *#
