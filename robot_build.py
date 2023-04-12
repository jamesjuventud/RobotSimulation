'''
robot_build.py

'''

import os
import platform
import sys
import argparse


#used for setting typing for mypy inspection
from typing import Dict, Tuple, List 

#globally set python executable name for use for invoking sub-commands
pyExecute = os.path.split(sys.executable)[-1]


class Build:
  '''Build: Class to house Build types
  Attributes
  ----------
  	bType : str
    	holds one of the pre-defined build type strings

  Methods
  -------
  	__init__(buildType = release)
    	Constructs a base version of our class and sets bType
  '''
  release = 'release'
  debug = 'debug'

  bType: str = release
  types: List[str] = [release, debug]
  def __init__(self, buildType = release):
    '''
    Build.init: Constructor, sets bType variable
    Parameters
    ----------
    	buildType : str
      	buildType to set; must be in types defined
    
    Returns
    -------
    	Initialized Object
    '''
	
    if buildType in self.types:
      self.bType = buildType
    else:
      print(f'type {buildType} is not a valid buildType')

def optExit():
  '''Exits run'''
  exit(1)

def getOptions(options):
  '''
  getOptions: parses arguments and sets options for generator/build
  Parameters
  ----------
  	options: Options object
  
  Returns
  -------
  	None
  '''
  parser = argparse.ArgumentParser(description='ROBOT Build x64 and x86 Python Script')

  parser.add_argument('--arch', nargs=1, choices=['x86', 'x64'], default=(['x86'], ['x64'])[is_linux], required=False,
                      help='The target architecture')

  parser.add_argument('--type', nargs=1, choices=['release', 'debug', 'all'], default=['all'], required=False,
                      help='The build type')

  parser.add_argument('--clean', action='store_true', default=False, required=False,
                      help='Perform a clean before building')

  args = parser.parse_args()

  options.x64 = (False, True)[args.arch == ['x64']]

  options.release = False
  options.debug = False
  if args.type == ['all']:
    options.builds.append(Build(Build.release))
    options.builds.append(Build(Build.debug))
  elif args.type == ['release']:
    options.builds.append(Build(Build.release))
  elif args.type == ['debug']:
    options.builds.append(Build(Build.debug))

  print('Build(s) selected:')
  for bt in options.builds:
    print(f'  {bt.bType}')

  options.clean = args.clean


class Options:
  '''Options: Class to house options from command-line
  Attributes
  ----------
  x64 : bool
    Used for Arch-setting between x64 and x86
  builds: list[Build]
    list of which build types to execute (like Release, Debug, ect)
  clean: bool
    Used to dictate if cmake and script clean existing build files to re-gen build completely
    Sets a CMake variable to try and prevent any CMake package publish commands from running
  '''
  x64 = False
  builds: List[Build] = []
  clean = False
  proj: List[str] = []
  version = ''
  noBuild = False
  sourcePath = '.'
  noPublish = False

def setup():
  '''
  setup: sets the cmake directory for builds
  '''
  global build_dir

  build_dir = 'build_win'
  build_dir += '_x64' if options.x64 else '_x86'

  if not os.path.isdir(build_dir):
    os.mkdir(build_dir)

def cleanPackage():
  '''
  cleanPackage: if cleanPackage.py exists, execute
  '''
  clean_script_name = 'cleanpackage.py'
  clean_script = os.path.join(cwd, clean_script_name)
  if options.sourcePath != '.':
    clean_script = os.path.join(options.sourcePath, clean_script_name)

  
  if (options.noPublish):
    print('Skipping CleanPackage as we are skipping publishing to it')
    return
  
  if os.path.exists(clean_script):
    print('Running cleanPackage step')
    cmd = pyExecute + ' ' + clean_script + ' --arch ' + ('x64' if options.x64 == True else 'x86')
    if os.system(cmd):
        print('CleanPackage step failed')
        sys.stdout.flush()


def clean():
  '''
  clean : if clean.py exists, execute
  '''

  clean_script_name = 'clean.py'
  clean_script = os.path.join(cwd, clean_script_name)
  if options.sourcePath != '.':
    clean_script = os.path.join(options.sourcePath, clean_script_name)

  
          
  
  if os.path.exists(clean_script):
      print('Running clean step')
      if os.system(pyExecute + ' ' + clean_script + ' --arch ' + 'x64' if options.x64 == True else 'x86'):
          print('Clean step failed')
          sys.stdout.flush()
          exitbuild(1)

def generate(buildType: str = Build.release):
  '''
  generate: sets up and issues cmake generator command
  Parameters
  ----------
  buildType: str
    Build type used to tailor generate command for that build type
  
  Returns
  -------
  None
  '''
  global output_dir
  generate_command = 'cmake -B' + build_dir + ' -S ' + options.sourcePath

  if buildType is Build.debug:
      generate_command += ' -DCMAKE_BUILD_TYPE=Debug'
      generate_command += ' -DCMAKE_DEBUG_POSTFIX=""'
  else:
    generate_command += ' -DCMAKE_BUILD_TYPE=Release'
    generate_command += ' -DCMAKE_DEBUG_POSTFIX=""'
  if options.x64:
      generate_command += ' -DARCH_TYPE=x64'
  else:
      generate_command += ' -DARCH_TYPE=x86'

  output_dir = os.path.join(cwd, build_dir, 'bin')

  if options.x64:
      generate_command += ' -G"Visual Studio 15 2017 Win64"'
  else:
      generate_command += ' -G"Visual Studio 15 2017"'

  generate_command += ' -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=' + output_dir
  generate_command += ' -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + output_dir
  generate_command += ' -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=' + output_dir

  #version
  generate_command += options.version

  if options.clean:
      cmake_cache = os.path.join(cwd, build_dir, 'CMakeCache.txt')
      if os.path.exists(cmake_cache): os.remove(cmake_cache)

  #always set so we don't have to clean to swap publishing types
  generate_command += ' -DBUILD_REQUEST_NO_PUBLISH='
  if (options.noPublish):
    generate_command += 'true'
  else:
    generate_command += 'false'

  #do not add any additional generate items beyond here!
  print('Running cmake to generate native build files : ' + generate_command)
  sys.stdout.flush()

  if os.system(generate_command):
      exitbuild(1)

def prebuild():
  '''
  prebuild: runs a prebuild script, if it exists
  '''  
  prebuild_script = os.path.join(cwd, 'prebuild.py')    
  if (options.sourcePath != '.'):
    prebuild_script = os.path.join(options.sourcePath, 'prebuild.py')

  if os.path.exists(prebuild_script):
      print('Running prebuild step')
      if os.system(pyExecute + ' ' + prebuild_script):
          print('Prebuild step failed')
          sys.stdout.flush()
          exitbuild(1)
        
def build(buildType: str = Build.release):
  '''
  build: sets up and issues cmake build command
  Parameters
  ----------
  	buildType: str
  		Build type used to tailor build command for that build type
  
  	Returns
  	-------
  		None
  '''
  build_command = ''
  cmake_args = ''

  if options.clean: cmake_args += ' --clean-first'

  if not is_linux:
    if buildType is Build.release: cmake_args += ' --config Release'

  if len(options.proj) > 0:
    cmake_args += ' --target'
    for proj in options.proj:
      cmake_args += ' ' + proj

  build_command += 'cmake --build ' + build_dir + cmake_args

  print('Running build : ' + build_command)
  sys.stdout.flush()
  if os.system(build_command):
      exitbuild(1)

def postbuild(buildType: str = Build.release):
  '''
  postbuild: executes postbuild script, if it exists
  Parameters
  ----------
  buildType: str
    Build type used to change bin_path and pass to postbuild script
  
  Returns
  -------
  None
  '''
  bin_path = output_dir

  postbuild_script = os.path.join(cwd, 'postbuild.py')
  if options.sourcePath != '.':
    postbuild_script = os.path.join(options.sourcePath, 'postbuild.py')

  if not is_linux:
      if buildType is Build.release:
          bin_path = os.path.join(bin_path, 'Release')
      else:
          bin_path = os.path.join(bin_path, 'Debug')
          
  
  if os.path.exists(postbuild_script):
      print('Running postbuild step')
      if os.system(pyExecute + ' ' + postbuild_script + ' --outputdir ' + bin_path):
          print('Postbuild step failed')
          sys.stdout.flush()
          exitbuild(1)
        
def exitbuild(code: int):
  '''
  exitbuild: cleans up the cwd and exits script with code
  Parameters
  ----------
  code: int
    int return code to use in exit() call
  
  Returns
  -------
  None
  '''
  print('Restoring current working directory')
  os.chdir(cwd)
  exit(code)


ostype = platform.system()
is_linux = ostype != 'Windows'

cwd = os.getcwd()

options = Options()
getOptions(options)



build_dir = ''
output_dir = ''
setup()
cleanPackage()
for bt in options.builds:
  if options.clean:
    clean()
	
  print(f'#################\nGenerating {bt.bType}\n#################')
  generate(bt.bType)
  
  if not options.noBuild:
    print(f'#################\nBuilding {bt.bType}\n#################')
    prebuild()
    build(bt.bType)
    postbuild(bt.bType)
  else:
    print(f'#################\nSkipping Build for {bt.bType}\n#################')
	
exitbuild(0)