Eugeni Soler Forn: eugeni.soler01@estudiant.upf.edu (253566)
Roger Viader : roger.viader01@estudiant.upf.edu (252282)

Per canviar entre exercicis, s'ha d'apretar el número de l'exercici. Es pot avançar de tasca amb "." i retrocedir amb ",".
EXERCICI 1 (shortcut: 1)
	a-f: tasques proposades
	g) Cor que batega

EXERCICI 2 (shortcut: 2)
	a-f: tasques proposades
	*e: Blur, però interactiu. Es pot augmentar el desenfocament amb "+"/"-" i, a més, on se situa el ratolí es fa una lupa que elimina el desenfocament.
	g) Flash
EXERCICI 3 (shortcut: 3)
	a) Rotació (es pot controlar la velocitat amb "+"/"-")
	b) Pixelat (es pot controlar el nombre de pixels amb "+"/"-")
	c) Distorsió RGB (també es pot controlar el desplaçament amb "+"/"-")
*En aquest exercici, el que es pot fer amb "+"/"-" també es pot fer amb la roda del ratolí. La diferència és que aquesta no té límit, mentre que les tecles tornen a 0 si el valor és molt alt. Es pot provar fàcilment amb la rotació.

EXERCICI 4 (shortcut: 4)
	Aquí "."/"," fa que puguis canviar la malla (Lee, Anna, Cleo)

CONTROL DE CÀMERA (entrega anterior)
- Ortographic/Perspective (shortcut O/P): canvia de porjecció ortogràfica a perspectiva. Pot ser necessari canviar valors de far/near o moure l'eye o el center per poder visualitzar les mesh.
- Moving (shortcut ARROWS): fan que es moguin alhora l'ull i el centre. UP i DOWN provoquen desplaçament en l'eix Y, i LEFT i RIGHT en l'eix X.
- Camera values: es canvien els 4 amb PageUp/PageDown depenen de si es volen incrementar o decrementar. Per modificar un dels valors cal prémer la tecla del seu shortcut abans. Per defecta es comença amb ZOOM.
	- Near/Far (shortcuts N/F): augmenta o disminueix els valors en 1 unitat.
	- FOV (shortcut V): s'augmenta o es disminueix l'angle de visió en 15º, amb un màxim de 180 i un mínim de 15.
- Zoom (wheel): s'apropa o s'allunya l'ull de la càmera (sumant el vector que els uneix) en un 10% cada vegada. 	
- Mouse Dragging té dues opcions: 
	- Orbit (shortcut R): mantenint clicat el ratolí i movent-lo. Si es mou de costat s'orbita un cert angle en l'eix X, i si es fa cap amunt o cap avall, s'orbita en leix Y. L'angle és proporcional al desplaçament. 
	S'aconsegueix orbitar agafant els vector que uneix center-eye i aplicant-li una rotació en X i en Y. Així la distància no varia perquè no hem canviat el mòdul.
	- Move Center (shortcut M): mou només el centre de la càmera, funciona igual que ORBIT però el desplaçament del ratolí ara es tradueix en un desplaçament en X i Y del centre de la càmera.