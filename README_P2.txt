Eugeni Soler Forn: eugeni.soler01@estudiant.upf.edu (253566)
Roger Viader : roger.viader01@estudiant.upf.edu (252282)

L'aplicació mostra una escena amb 3 mesh de colors diferents. Una rota sobre si mateixa, l'altra està constantment escalant-se i l'última es va movent a posicions aleatòries.
El funcionament de l'aplicació es pot fer mitjançant el ratolí (dragging) o prement botons del teclat.
Les funcionalitats són:

- Ortographic/Perspective (shortcut O/P): canvia de porjecció ortogràfica a perspectiva. Pot ser necessari canviar valors de far/near o moure l'eye o el center per poder visualitzar les mesh.
- Moving (shortcut ARROWS): UP i DOWN fan que es moguin alhora l'ull i el centre en l'eix Y, i LEFT i RIGHT provoquen moure's en l'eix X.
- Camera values: es canvien els 4 amb PageUp/PageDown depenen de si es volen incrementar o decrementar. Per modificar un dels valors cal prémer la tecla del seu shortcut abans. Per defecta es comença amb ZOOM.
	- Zoom (shortcut Z): s'apropa o s'allunya l'ull de la càmera (sumant el vector que els uneix) en un 10% cada vegada. 
	- Near/Far (shortcuts N/F): augmenta o disminueix els valors en 1 unitat.
	- FOV (shortcut V): s'augmenta o es disminueix l'angle de visió en 15º, amb un màxim de 180 i un mínim de 15.
- Orbit around center: es pot fer mantenint clicat el ratolí i movent-lo. Si es mou de costat s'orbita un cert angle en l'eix X, i si es fa cap amunt o cap avall, s'orbita en leix Y. L'angle és proporcional al desplaçament.