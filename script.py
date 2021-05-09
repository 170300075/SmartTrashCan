#!/home/kenneth/environments/base/bin/python3.8

print("content-type: text/plain\n\n")
import cgi
import cgitb
import os
cgitb.enable()

# Recibimos los archivos por post
form = cgi.FieldStorage()
# Almacenamos el archivo de la imagen
fileitem = form["imagen"]

# Si la imagen existe
if fileitem.filename:
    # obtenemos el nombre de la imagen subida
    fn = os.path.basename(fileitem.filename)
    # y la abrimos un archivo y escribimos la imagen en binario
    open(fn, 'wb').write(fileitem.file.read())

    message = "Archivo subido exitosamente"

else:
    message = "Archivo no fue subido"

print(message)

# Escribir el código de reconocimiento de 
# imagenes aquí
