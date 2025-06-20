import os
import subprocess
def build_cmake_project(build_dir='../build'):
    # Crear carpeta build si no existe
    os.makedirs(build_dir, exist_ok=True)

    # Paso 1: ejecutar cmake ..
    cmake_cmd = ['cmake', '..']
    print("Ejecutando:", ' '.join(cmake_cmd))
    subprocess.run(cmake_cmd, cwd=build_dir, check=True)

    # Paso 2: compilar con make
    make_cmd = ['cmake', '--build', '.', '--config', 'Release']
    #make_cmd = ['cmake', '--build', '.']
    print("Ejecutando:", ' '.join(make_cmd))
    subprocess.run(make_cmd, cwd=build_dir, check=True)
