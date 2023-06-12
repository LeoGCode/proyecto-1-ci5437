Para generar las pdbs de los problemas
ejecutar:

$ make all

Se generaran las especificaciones en psvn, de la abstraccion y finalmente las PDBs
Los archivos .txt de los directorios asociados al problema especifican
las proyecciones y abstracciones asociadas a cada pdb.


Ademas es necesario que en la raiz del programa exista el directorio
psvn/global con los siguientes archivos:
- generator.cpp
- dist.cpp
- distSummary.cpp
- priority_queue.cpp