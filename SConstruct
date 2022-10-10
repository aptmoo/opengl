sysinc = '/usr/include/'
syslib = '/usr/lib/'
localinc = ['src/', 'include/']
libs = ['GLEW', 'glfw', 'GL']

flags =['-O2', '-std=gnu++17', '-w', '-DGLEW_STATIC', '-DDEBUG', '-DLOGFILE']

basefiles = ['src/pch.h',Glob('src/*.cpp'), Glob('src/gl/*.cpp')]

editorfiles = []
Program('bin/app', basefiles + editorfiles,CCFLAGS=flags, CPPPATH=[sysinc, localinc], LIBPATH=[syslib],LIBS=[libs])
