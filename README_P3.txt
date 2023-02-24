Eugeni Soler Forn: eugeni.soler01@estudiant.upf.edu (253566)
Roger Viader : roger.viader01@estudiant.upf.edu (252282)

Les funcionalitats de l'aplicació són molt semblants a les de l'entrega anterior, però com que hem escrit el codi a sobre algunes han canviat.
Hem volgut emular el que se'ns donava d'exemple al release del Lab 3. 
Es mostra el que sembla una Entity, però en realitat són dues sobreposades (a les mateixes coordenades i amb el mateix escalat).
Una d'elles només es renderitza si els pixels detots els vèrtexs del triangle estan a la meitat esquerra i l'altra si estan a la meitat dreta i entremig dibuixem una línia blanca que les separi. Hi ha alguns triangles en què els vèrtexs cauen a les dues meitats, i es veu una mica estrany a la frontera, però el resultat final és satisfactori.

CONTROL DEL RENDER
- Toggle color (shortcut C): fa que es pintin o no els triangles (aplica només a la malla esquerra) 
- Toggle wireframe (shortcut W): canvia entre Wirefreame i Pointcloud (aplica només a la malla esquerra)
- Toggle occlusions (shortcut Z): fa que s'actualitzi o no el zBuffer quan pintem un píxel
- Toggle textures (shortcut T): fa que s'accedeixin als texels i es pinti amb textura o amb colors de malla (aplica només a la malla dreta)

CONTROL DE CÀMERA (entrega anterior)
- Ortographic/Perspective (shortcut O/P): canvia de porjecció ortogràfica a perspectiva. Pot ser necessari canviar valors de far/near o moure l'eye o el center per poder visualitzar les mesh.
- Moving (shortcut ARROWS): UP i DOWN fan que es moguin alhora l'ull i el centre en l'eix Y, i LEFT i RIGHT provoquen moure's en l'eix X.
- Camera values: es canvien els 4 amb PageUp/PageDown depenen de si es volen incrementar o decrementar. Per modificar un dels valors cal prémer la tecla del seu shortcut abans. Per defecta es comença amb ZOOM.
	- Zoom (wheel): s'apropa o s'allunya l'ull de la càmera (sumant el vector que els uneix) en un 10% cada vegada. 
	- Near/Far (shortcuts N/F): augmenta o disminueix els valors en 1 unitat.
	- FOV (shortcut V): s'augmenta o es disminueix l'angle de visió en 15º, amb un màxim de 180 i un mínim de 15.
- Mouse Dragging té dues opcions: 
	- Orbit (shortcut R): mantenint clicat el ratolí i movent-lo. Si es mou de costat s'orbita un cert angle en l'eix X, i si es fa cap amunt o cap avall, s'orbita en leix Y. L'angle és proporcional al desplaçament. 
	S'aconsegueix orbitar agafant els vector que uneix center-eye i aplicant-li una rotació en X i en Y. Així la distància no varia perquè no hem canviat el mòdul.
	- Move Center (shortcut M): mou només el centre de la càmera, funciona igual que ORBIT però el desplaçament del ratolí ara es tradueix en un desplaçament en X i Y del centre de la càmera.