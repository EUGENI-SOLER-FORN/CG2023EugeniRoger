Eugeni Soler Forn: eugeni.soler01@estudiant.upf.edu (253566)
Roger Viader : roger.viader01@estudiant.upf.edu (252282)

El funcionament de l'aplicació es pot fer mitjançant la barra de tasques (que hem editat per ampliar les funcions) o prement botons del teclat.
A la toolbar original hi hem afegit botons. Les funcionalitats són:
- SAVE (shortcut: S): guarda una imatge de la pantalla actual, a la carpeta principal, amb el nom de "myDrawing.tga"
- NEW (shortcut: N / scape): borra el framebuffer i omple la pantalla de blanc.
- COLORS: Canvia el color amb el qual estem dibuixant, hi ha les opcions de negre, vermell, verd, blau, groc, lila, cyan, magenta i blanc.
- MODE FREEHAND (shortcut: F): permet dibuixar mentre es prem i es mou el cursor, lliurement, amb la funció de DrawLineBresenham).
- MODE LINE (shortcut: L): per dibuixar una línia s'ha de prémer el cursor en el punt inicial, i desplaçar-se (sense aixecar el cursor) fins al punt final.
- MODE CIRCLE (shortcut: E): per dibuixar una circumferència s'ha de prémer el cursor en el punt que vulguem com a centre, i desplaçar-se (sense aixecar el cursor) fins on vulguem que arribi el cercle (la distància que ens haguem desplaçat serà el radi.
- MODE FILL_CIRCLE (shortcut: C): el mateix que CIRCLE, però ara l'interior del cercle s'omplirà amb el color que tinguem triat.
- MODE PARTICLE (shortcut: P): amaga la toolbar i mostra una animació tipus "flocs de neu" amb 200 partícules de mida variant que floten fins a baix i tornen a dalt. Per sortir de l'animació i tornar al mode FREEHAND, cal prémer DELETE però el canvas tornarà a ser blanc.

Les partícules de l'animació són sempre sobre fons Negre, però el color de les partícules és el que s'està fent servir per dibuixar (si és negre també, no es veu res).
Es pot guardar una captura de l'animació prememnt S igualment. Quan es guarda uan captura del canvas, la toolbar apareix a baix.