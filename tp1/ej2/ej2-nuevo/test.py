import os
import subprocess

def test(testCase):
    cmd = ['echo', str(testCase), '| ./ej2'] #seguro se puede hacer mejor lo del pipe
    output = subprocess.check_output(cmd)
    output.split()
    size_izq = int(output[0])
    size_der = int(output[1])
    suma = 0
    for j in range(2,size_izq):
        suma = suma + int(output[j])
    for k in range(2 + size_izq, 2 + size_izq + size_der):
        suma = suma - int(output[k])
    if suma == 0:
        print('Caso '++ str(testCase) ++ 'paso el test correctamente')
    else:
        print('Caso '++ str(testCase) ++ 'fallo el test')
        print('Suma: ' ++ suma)


