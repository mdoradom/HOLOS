**Hands On Lab: Memoria**

**Juanjo Costa <<jcosta@ac.upc.edu>>**

**Mon, 16 Apr 2023**

Objectius
=========
- Avaluar el rendiment d'un codi (temps d'execució, cicles)
- Detectar el patró d'accés a memoria d'un codi
- Entendre l'impacte de la cache en un codi
- Utilització bàsica de funcions per gestionar memòria dinàmica
- Ús de GPU


Estructura de directoris
========================
En el codi suministrat es troben els següents directoris cadascun amb el codi
font necessari per les següents seccions:

- 1_matrix (Avaluació de rendiment)
- 2_access_pattern (Patró d'accés)
- 3_dynamic_memory (Memòria dinàmica)
- tools (Utilitats per mesurar temps i anàlisi)


Avaluació de Rendiment
======================
És important saber avaluar el rendiment dels nostres codis. Saber el que
triguem a fer les coses. En el nostre context (videojocs) és imprescindible
ja que això defineix el rendiment dels nostres jocs, el nombre de frames que
puc mostrar per segon. Quant menys trigui a "calcular" el frame, més frames
puc generar.

Mesurar el que triga un tros de codi és relativament simple si tinc una funció
_capturarTemps_ que funcioni com un cronómetre:

```
	...
	t1 = capturarTemps();

	// Tros de codi a mesurar

	t2 = capturarTemps();
	temps = t2 - t1; //Temps que trigo a executar el codi
	...
```

L'únic problema és que la resolució i el cost d'aquest _capturarTemps_ depén
del hardware i del sistema operatiu usat. En el cas de Windows(TM), la seva
documentació ens en dona una explicació força detallada [[TIME]].

Per que et donis una idea, al fitxer _measure.c_, trobaràs les rutines
_start_counter_ i _get_counter_ que bàsicament serveixen com a cronòmetre,
retornant el nombre de microsegons que han passat entre les dues crides.
Aquestes rutines funcionen tant a Windows com a Linux.

Un problema addicional és que el temps que triga un determinat codi no és sempre
exactament el mateix degut a la complexitat dels factors que hi intervenen
avui dia. El codi a measurar no s'executa directament sobre l'arquitectura, sino
que hi ha un sistema operatiu, dispositius que interrompen el flux habitual
d'execució, ... per tant, el que fem habitualment és executar el mateix codi
diversos cop i fer un anàlisi estadístic sobre els temps resultants per quedar-nos amb
el valor més estable.

La rutina _measure_full_, que pots trobar al fitxer _measure.c_, automatitza
aquest procés i retorna el mínim temps d'execució d'un codi. En concret,
executa el codi varios cops, mesura el seu temps d'execució a cada iteració i
guarda aquests valors en una taula fins que la diferencia de temps entre els
valors més petits sigui menor d'un 1 per cent (1% o 0.01), que és el factor que
hem decidit per considerar una mesura de temps suficientment estable. Aquesta
rutina és la que usem per calcular els temps d'execució en els següents
exercicis.


Avaluant matrius...
-------------------
Per començar anem a avaluar un codi molt simple de recorregut de matrius, per
veure si triguem el mateix fent un recorregut per files o per columnes.
Veurem que per matrius petites, els dos recorreguts són semblant, però per
matrius grans... això ja no és cert.

Al fitxer _matriu.c_ tens un codi que recorre una matriu molt petita (8x8).
El codi mostra el temps en microsegons que triga fent el recorregut per files i
pel recorregut per columnes. Aquest temps és el menor d'executar fins a 10 cops
el mateix codi, avaluant que l'error entre els 3 valors més baixos sigui
inferior a un 1% (0.01).

Per fer l'avaluació compilarem i executarem l'aplicació diverses vegades,
anotant el temps d'execució per cadascun dels recorreguts i anirem incrementant
les mides de les files i les columnes de la matriu (sempre amb el mateix valor
a totes dues) en potencies de 2 (8, 16, 32, ...).


- Fes una taula amb la mida de la matriu i els temps d'execució pels dos recorreguts.

Matrix Size | Time init | Time row 1 | Time row 2 | Time row 3 | Time col 1 | Time col 2 | Time col 3
-- | -- | -- | -- | -- | -- | -- | -- |
`16 x 16` | 0μs | 0μs | 0μs | 0μs | 0μs | 0μs | 0μs
`32 x 32` | 2μs | 2μs | 2μs | 2μs | 3μs | 2μs | 2μs
`64 x 64` | 6μs | 6μs | 6μs | 6μs | 3μs | 3μs | 3μs
`128 x 128` | 19μs | 21μs | 10μs | 19μs | 16μs | 13μs | 15μs
`256 x 256` | 62μs | 63μs | 63μs | 63μs | 114μs | 116μs | 116μs
`512 x 512` | 343μs | 332μs | 332μs | 332μs | 508μs | 503μs | 503μs
`1024 x 1024` | 1319μs | 1324μs | 1323μs | 1321μs | 6663μs | 5364μs | 6067μs
`2048 x 2048` | 5293μs | 5312μs | 5296μs | 5320μs | 31473μs | 31377μs | 31384μs
`4096 x 4096` | 14514μs | 15338μs | 14309μs | 14742μs | 108086μs | 105834μs | 105835μs

![](https://i.imgur.com/7SiXuV6.png)

- **Es similar el temps d’execució quan es recorre per files de quan es recorre per columnes? (Assegurat de fer un parell d'execucions per estar-ne segurs)**

Dependiendo del tamaño de la matriz. Como podemos observar en la tabla superior, con valores mas pequeños como el de ``16x16`` o ``32x32``, los tiempos de acceso se estabilizan tanto para las columnas como para las filas. 

En cuanto subimos a tamaños un poco mas grandes, como ``64x64`` o ``128x128``, los tiempos de acceso son mas cortos para las columas que para las filas. 

Si probamos con tamaños iguales o superiores a ``256x256``, los tiempos de acceso cambian, pasamos a tener tiempos de acceso menores en las filas que en las columas, aumentando esta diferencia en cuanto mas grande sea la matriz en cuestión.

- **A la vista de la taula, què en pots extreure? Hi ha algun canvi en els temps d'execucció entre els 2 recorreguts?  Quant ocupa 1 fila? Per què creus que passa?**

Los tiempos de ejecución varian segun el tamaño de la matriz y si estamos accediendo a la fila o la columna.

El tamaño de una fila varia dependiendo el tamaño de una matriz. Si por ejemplo tenemos una matriz de ``4096 x 4096``, el tanaño de una fila será `4096`, haciendo un calculo rápido podemos ver que el tamaño de una fila de una matriz ``4096 x 4096`` es de unos **4KB** *(4096 / 1000 = 4,096KB)*

- **Comprova els nivells de cache del teu processador [[CPUDB]] amb els resultats que t'han sortit a la taula.**

```
CPU
	11th Gen Intel(R) Core(TM) i7-11700 @ 2.50GHz

	Velocitat base:			2,50 GHz
	Sòcols:					1
	Nuclis:					8
	Processadors lògics:	16
	Virtualització:			Habilitat
	Cache L1:				80K (per core)
	Cache L2:				512K (per core)
	Cache L3:				16MB (shared)
```

En tamaños mas peuqeños donde la matriz se puede cargar integra en la cache L1, los tiempos de ejecución son muy rapidos y practicamente iguales para filas y columnas, pero en cuanto el tamaño de la matriz empieza a aumentar y no la podemos meter entera en la L1, hay que cargarla en la L2 o incluso la L3, perjudicando así el tiempo de ejecución. Por que vemos ese aumento de tiempo de acceso a las columnas? Es sencillo, al tener que acceder primero desde la columna y luego desde la fila, cargando ambos elementos y teniendo que hacer saltos mas grandes, es muy probable que el elemento que estemos intentado acceder, esté fuera de la cache de nivel mas bajo.


Patrons d'accés i impacte de la cache
-------------------------------------
Les estructures que usem per guardar informació (com les matrius) s'han de
linearitzar per guardar-se a memoria (com varem veure a teoria). I per tant el
patró d'accés a aquestes estructures afecta al rendiment (tal i com hem vist a
l'apartat anterior). Anem a veure de quina manera exactament.

En el següent exercici presentem 3 programes: _mm-ijk.c, mm-jki.c i mm-kij.c_.
Corresponen a 3 de les 6 formes ijk del producte de matrius. Per exemple, en el
programa _mm-ijk.c_ es mesura la següent porció de codi (ijk vol dir que el bucle
més extern és el bucle controlat per la variable 'i' i el més intern és el
controlat per 'k'):

```
	for (i=0; i<N; i++)
		for (j=0; j<N; j++)
			for (k=0; k<N; k++)
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
```

Els 3 programes realitzen, de forma diferent, la mateixa operació: el producte
de matrius: C = A * B.

Hi ha una macro que defineix la mida de les matrius, per defecte de 256x256 floats:
```
	#ifndef N
	#define N 256  /* Dimensión por defecto */
	#endif
```
Si aquesta mida es N=6 (o més petit), mostra el contingut de la matriu
resultat C, de forma que puguis comprovar que els 3 programes fan el mateix.
Si és més gran, només fa el producte i mostra el temps d'execució en milisegons.

Pel següents exercicis, tria 1 dels casos.

- Es important saber l'ordre d'accés als elements de memòria d'un codi
  qualsevol. Per exemple, en el codi anterior la matriu C s'accedeix mitjançant
  C[i][j] i per tant segons l'ordre dels bucles 'i' i 'j', s'estan accedint als
  elements :
```
        C[0][0], C[0][1], C[0][2], ... C[0][N],
        C[1][0], C[1][1], C[1][2], ... C[1][N],
        ...
```
  Es a dir, s'accedeix a tots els elements de la 1a fila, després a tots els de
  la 2a, i així per totes les files.
  Dibuixa, pel cas triat, l'ordre en el que es recorren les matrius A, B i C
  (com a exemple, ja es mostra l'accés de la matriu C):

```
            +-------------+ +-------------+ +-------------+
            | (1)-------> | | (1)-------> | | (1) (2) ... |
            | (2)-------> | | (2)-------> | |  |   |      |
            | ...         | | ...         | |  |   |      |
     mm-ijk |      C      | |      A      | |  v   v B    |
            |             | |             | |             |
            |             | |             | |             |
            |             | |             | |             |
            +-------------+ +-------------+ +-------------+

            +-------------+ +-------------+ +-------------+
            |             | |             | |             |
            |             | |             | |             |
            |             | |             | |             |
     mm-jki |      C      | |      A      | |      B      |
            |             | |             | |             |
            |             | |             | |             |
            |             | |             | |             |
            +-------------+ +-------------+ +-------------+

            +-------------+ +-------------+ +-------------+
            |             | |             | |             |
            |             | |             | |             |
            |             | |             | |             |
     mm-kij |      C      | |      A      | |      B      |
            |             | |             | |             |
            |             | |             | |             |
            |             | |             | |             |
            +-------------+ +-------------+ +-------------+
```

- Apunta el temps d'execució per la versió triada:
```
		   | Temps execució (en ms)
		 N | mm-ijk			| mm-jki | mm-kij
	-------+--------+--------+--------
	   256 | 40.55200	 	|        |
	   512 | 380.23700		|        |
	  1024 | 2549.577000	|        |
```

- Supossant que cada element de la matriu ocupa 4 bytes, i que la mida
de pàgina del nostre sistema és de 4Kbytes calcula pel cas triat el nombre
de pàgines de memòria virtual que s'usen a l'executar completament el bucle més
intern 1 cop.
Per exemple, en el cas mm-ijk, per cada execució de tot el bucle 'k' la matriu
C només accedeix a 1 element (4bytes), mentres que la matriu A accedeix a tota
1 fila (elements consecutius) i la matriu B a tota 1 columna (elements no
consecutius).

```
		   |             mm-ijk             |
		 N | matriu A | matriu B | matriu C |
	-------+----------+----------+----------+
	   256 |    1     |    64    |    1     |
	   512 |    2     |    128   |    1     |
	  1024 |    4     |    256   |    1     |
	-------+----------+----------+----------+

		   |             mm-jki             |
		 N | matriu A | matriu B | matriu C |
	-------+----------+----------+----------+
	   256 |          |          |          |
	   512 |          |          |          |
	  1024 |          |          |          |
	-------+----------+----------+----------+

		   |             mm-kij             |
		 N | matriu A | matriu B | matriu C |
	-------+----------+----------+----------+
	   256 |          |          |          |
	   512 |          |          |          |
	  1024 |          |          |          |
	-------+----------+----------+----------+
```



Memòria dinàmica
================
Les rutines de _malloc_ i _free_ de la llibreria de C permeten a un programa
d'usuari demanar memoria dinàmica al sistema operatiu. El sistema operatiu
assigna nou espai al procés, però degut a que la granularitat de la crida
(demana bytes) i la granularitat del SO (reserva i mapeja pàgines de 4096 bytes)
no coincideixen, pot passar que l'usuari pugui executar codi no legal.

El fitxer _mem.c_ conté un codi que reserva un vector de 10 caracters i
inicialitza les seves posicions. A continuació intenta accedir a
posicions fora d'aquest vector.

- Executa el codi,  observa el resultat i intenta deduir què està pasant.

Estamos reservando en memoria espacio suficiente para almacenar los 10 elementos que ejecuta el programa, en la primera iteración, almacenamos los 10 elementos en los espacios que hemos guardado para ello de forma correcta, pero en cuanto damos enter para seguir el flujo del programa, intentamos acceder a las siguentes posiciones, las cuales están fuera de la memoria que hemos reservado, pero nos deja acceder, lo cual es un acceso incorrecto. Cuando hacemos el malloc(), realmente reservamos mas espacio en memoria del que pedimos, así que realmente no salimos de la memoria reservada para el programa, pero en cuanto llegamos al bucle infinito, estaremos iterando por esa memoria reservada hasta salirnos y lanzar una excepción.

El fitxer _mem2.c_ mostra els efectes perniciosos d'usar memòria que no hem
reservat explícitament.

- Executa el codi,  observa el resultat i intenta deduir què està pasant.

Aquí sucede lo mismo, lo único es que podemos ver que cuando hacemos un free de esos espacios de memoria, podemos reutilizarlo para volver a guardar elementos.

GPU fun
=======
Avui dia, tot i que la cache és important, en el context dels videojocs, la
càrrega de feina se l'emporta la GPU i per tant cal tenir-ho present.
A [[GPU]] el Keith O’Conor (programador i CTO de [[Romero Games]]) dona una molt
bona explicació de l'importància de les GPUs (i prou referencies per estar
entretinguts tot el temps que volgueu)


References
==========

[TIME]: https://docs.microsoft.com/es-es/windows/desktop/SysInfo/acquiring-high-resolution-time-stamps "Acquiring high-resolution time stamps"
[CSAPP]: http://csapp.cs.cmu.edu/2e/home.html "Computer Systems: A Programmer's Perspective. Randal E. Bryant and David R. O'Hallaron, Carnegie Mellon University, 3rEdition"
[MOUNT]: http://csapp.cs.cmu.edu/3e/mountain.tar "Memory Mountain source code"
[CPUDB]: https://www.techpowerup.com/cpudb/ "CPU Database"
[GPU]:  http://www.fragmentbuffer.com/gpu-performance-for-game-artists/ "GPU performance for game artists. Keith O'Conor"
[Romero Games]: https://www.romerogames.ie/
..[[TIME]]: https://docs.microsoft.com/es-es/windows/desktop/SysInfo/acquiring-high-resolution-time-stamps "Acquiring high-resolution time stamps"

..[[CSAPP]]: http://csapp.cs.cmu.edu/2e/home.html "Computer Systems: A Programmer's Perspective. Randal E. Bryant and David R. O'Hallaron, Carnegie Mellon University, 3rEdition"

..[[MOUNT]]: http://csapp.cs.cmu.edu/3e/mountain.tar "Memory Mountain source code"

..[[CPUDB]]: https://www.techpowerup.com/cpudb/ "CPU Database"

..[[GPU]]:  http://www.fragmentbuffer.com/gpu-performance-for-game-artists/ "GPU performance for game artists. Keith O'Conor"

..[[Romero Games]]: https://www.romerogames.ie/
