//Game title + logo
const char* gameTitle = R"(
                 : .::;;;;;+XX:    :$&&&&&&&&&&&&&&&&&&$+.                 .....   .+xx: ....  .+::::.:::: :.+$$x.    ;XXX$:....:;$$$$$$$$$$XX$Xx;;;;;+xX$&&&&&&&&&&&&$$$$$$$$$$$$$$XXXx+;;;+xX$&&&        
                   .:::;;;.  :x&&&&&&&&&&&&&&&&&&&&&&&&x:                         ... +xx:. ;:;+X+:::::;;x++;;$$$$.     +$$$+...;XXXXXXXXXx;;;;;;+;    ;$$$$&&&&&&&&&&&&&&&&&$$$$$$$$$$$XXXXXX$$$&&        
                   .:;;;  x$$$$$$$&$$&&&&&&&&&&&&&$$$&&&;.                             +XXX+:x+$$$xX:+++x$$X+$$$&&&:      X$X$;:$XxxxXXxxx+:..;+XX$X..;$$$&&&&&&&&&&&&&&&&&&&&&&&&$$$$$$$$$$$$$$&&&        
                  .::;. X$XX$$&&&&&$$XX$&&&&&&&&$x++xX$&$X                              .xXXXX$$$$$$$$$$$$$&$&&&&&&&x . .. .$$$$&$$Xx;xxx+;.:;xX$$&$X$XXXXX$$$$$&&&&&&&&&&&&&&&&&&&&&&$$$$&$$$$$&&&        
                  .:: x$x++$$$$$$$$$$XxxX$$&&&$Xxx+;;;XX$&$.             :              . xXX$$$$$$$$$$&$&$&&&&&&&&&&&x:     ;$$$&&+ $Xx+;.:;xXX$&&&$$$$X$X..:+x$$$$$$&&&&&&&&&&&&&&&&&&$$$&&&&&&&&        
                  ..:$X+:;xXxx++xxxx$xx++X$$&Xxxxx++;;;XX$&&; .     .    :       +;       .+$$$$$$$$$&$&&&&$&&&&X+xx$&&&+      .X$X$$&$X+;:+xXXX&$XX&&&&&$$;..   .;+xxxXXx$$&&&&&&&&&&&&&&&&&&&&&&&        
                   +xx+  ;;X     .::X;;:.+xX$xx++++;::..XX$&$:    :.;   .:        .   .     ;X$$$$$$&&&&&&&&&&X;:+xxxx$&&&+ .;$$XX$$$$&$x++xxXX&Xx+$&&&&&&&&$$+:..    .::;;++x+X$$$$$&&&&&&&&&&&&&&        
                 .++++. ..                +xXx+;;;;: ...+X+&&X:  : . .  ;$        x     . :.  .;X&$+&&+$&&&&X.  .;+xxxX&&&&;x&$+xX$$$X$x+x$$$$&&++&&&&&&&&&&&$&&$$x;;:        +X$$$$&&&&&&&&&&&&&&&        
                ;::;;:       ...:::x;;;.  +xx+;;;:.   ::$X:&&&X+; :;::.;..$X:.     X     .;:.+   .x+$&+Xx:      :;++++x$&&&xX&$+::x$$Xx+;X&&&&&:x:$&&&&&&&&&&$&&&&&&X;;;:.  .+xXXxxX$$&&&&&&&&&&&&&        
              .. ..:.     ;.:;;++++Xxx+;:  xxx:.     :;XX:x&&&&&&$xx+:.::.+.Xx.     X+     :Xx.; .;Xx&:+        .:;+x+xX$&&&&&&X .:XXXx+xx$$&&& x.$$$&&&&&&X&&&&&&&&&&&&$XX;+X$X  xXX$&&&&&&&&&&&&&        
                         :+;++xXxxX$XXXx;. .$:.       .X$+&&&&&&&&&&&&$$XXxX;:x$:    XX      ;XX;;;++X:+        :;;+++xx++X$&&&&x+;;;;;+xXX$$$$X;x+$$$$&&&XX&$&&&&&&&&&&&&&&$$$$x;XX$$$$&&&&&&&&&&&        
                        .:++xxXXXX$$$$XX+.            :Xx:&&&&&&&&&&&&&&&&&&&X;;+&x:: +$X      ;XX+;+:;;.        :;;++;+X$$&&&&&&&&$X;:.:+xXxXXXXXX$X$&&&$$$$Xx$&&&&&&&&&&&&&&$XXXX$$$$$$$&&&&&&&&&        
                         +++xxXXXX$$$$XXx;.           +Xx.&&&&&&&&&&&&&&&&&$$$&X;X&+::::X&X      xxx+.xx;       .:::+:X$$$$&&$$&&$XX+++xX+:.:;;++x+;xX$$&&$$$$$+&&&&&&&&&&&&&;::;+xxXX$$&&&&&&&&&&&        
                         +:++xXXXX$&$$$Xx+x           ;xx.&&&&&&&&&&&&&$$$XXXXX$$&&$:;;+++&&$      ;x;;: .x. .. ..;:+$$$$$$$$&&$XXX+;;+X$&&$:.....:+X$X$$$&$$$$&;$&&&&&&&&&&&&;   xxXX$&&&&&&&&&&&&        
                         +.:++XXXX&$$$$X+              ;: ;&&&&&&&&&&&$$Xx;:::+x$$$&x;+xXX&&&&X          ;++;XXX$$X$$$$$$$$$&$XXxx++;++x$$&$&;:.   :xXX$$$&$$$&&&x$&&&&&&&&&&&X  .+xX$$$$&&&&&&&&&&        
                          .:;+xXX$&&$$$:           .x+.;X&&&&&&&&&&&&&$$Xx:  .;xX$$&&&Xxx$&&&&&$+     .+xxxXX$$$$&&&&&$$$&&&$x+;;;;++xxX$$$$$$..  :XX$$XXX$$$&&&&;.$$$&&&&&$&&$  .+XX&&&XX&&&&&&&&&        
                           ..:xXXX&$$$$.        .       +X;:X&&&&&&&&&$$$$XxxxX$$$$&&&&&&&&&&&&&&x  :x$X;;:;;::;+$&&&&&&&&&$$X++++++xXX$$$$$$X: .:X$$+:XXX$X$&&+ ;+$$XXXX$;$$$&.  +x$&. :XX$&&&&&&&        
                           .. +XX$&&&$$$                :X$;;$&&&&&&&&$$$$$$$$$$$$&&&&&&&&&&&&&&&&;:;$$X;+;:xXXXX+$&&&&&&&$$$$$$$XXx;;+xXxx++:+xX$$$.::$; :XX$ xx;$$XX$X::X$$$+: .;xX. X.  :$&&&&&&        
                  ...  ..   .:XXX$&$$$$$$ .               x$X::$&&&&&&&&&$&&&$&&&&&&&&&&&&&&&&&&&&&&&$&X:   ;x::;;;$&&&&&&&$$$$$$$$X+::+xX$xx$$$$$:::..::+$$X$&x.&&&$X$ +$XX$$X. .;;x:&Xxx+X$&&&&&&        
                 .::::.;;   . ;+X&$$$$$XX:                  ;x+;;$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$X$&&&&&$;   :::::::.+&&&&&&&&&&$$$$$$$$$$$xxX$$$X$:xx::X&$XX$$$x&&&&$$$Xx$$$x:+:+$$$Xx&X$&&&&$$$&&&        
                ..::::.+;     :;X$$$$XXx++                +$+:;+xXXX++$&&&&&&&&&&&&&&&&&&&XX&Xxx+:x$&&$$$X;   ..::::::+XXXx++xX$&&&&&&Xx$&&&&&$$&$xx::::x$XXX$X$&&&&&&&&&&&&&&$  ;XX&&&&&&&&&&&&&&&        
                ..::::;x:     :;X$XXXxx;:+     ;;     :Xx       XXx;:::;$&&&&&$x+;:::+;:+X$+++;::;;;++X&&&&&&$. .:::;:::;$$$XXXX$X+++X$$$$$$$x$&&&&&Xx:::+xXX$$X .x$:$&&&&&&&&+ ..X$$&&&&&&&&&$&&&&        
                 .::::+x:.   .:;+Xxx+;:          +   $            $$:  .x$$$x;:::. .:x;+;;: +$$$$.X;;+X&&&&&&&&&+  :;::;:  :x;.:;xXXXXXXX:;+xX$&&&&&&&$x:::+X+.:x  . :X&&&&&&&    X$$&&&&X&$$$$$&&&        
                    .:+;:    ..:;x+;.           .+   .            x.  .;;;.;;  +$&&&&&&&;     .:  X;;;X&&$$$$$&&&&;    ;+;...   X     ..;:;;+x$&&&&&&&&&$;;:X + ;.    +X&&&&X   xXX$$&&&&&&$$$$$&&&        
                     .x:.       ::.               . .   .:               .::::X$$$$$$$X$;         ::::x$$$$$$$$$&&&&       +x$XX$      .:::;;x$&&&&&&&&$X:x+x.X+ ;  .x&&&&&&.  :xXX$$$&&&&&&$$$$$&&        
                     :;:.       ..    .;;;+;xx     : .   .                ..:::.xX$XXXX.           .::X$XXXX$XXX$$$&$   .XX$:.. .; ;XX;.:::;;+$&&&&&&&X&&&$XX$:xxXXX&&&&&&&&$.   ...;X&&&&&$$$$$$$&        
                     :::            ;+xxxXXX$$$X  ..+. .:+.           ;x+;::::...x$$$X            .::;+$XXXXXXXXXxXX$   xX$. .:X+  xXX&$$$x+++xX$&&&X$&&$$&&:::x$$$&&&&&&&&&& xXxX$$X$&&&&$$&$$$$$&        
                     ;..          ;+xxXX$$$$$$&&&X .::++.+...  .:;X$$$$$$&&&&&;..:X$$$           :&$&&&;XXXXXXXXXX$X+X&&$&&$Xx.  $$$XXx$$&$&&&X$XXX$&&XX&&&&X::;X$&&&$$$&&&&&$  ..X&&&&&$$$&&$$$$$&        
                    .:           ++xXX$$$$$$$&&&&&&+;;;xxXXXXXXXXX$$$$&&&&&&&&&X:..$$&          .$&&&&&XX$XXXXXXXXX ....x&$:     .+$XXXxX&$&&&&&&&&&X+&&&&&&&. ..:;X$$$&&&&&x.;xXXxx+;+$&&&$$$$$&&&        
                    ;           .++xXX$$$$$XXX$$$&&&$xxxxXX$$$$$XXXX$$&$&&;X&&&&$;..;X.         ;&&&&&&$x$XXXXXxXX;    +&&&&++x+:::.;xXxxX$&&&&&&&&$X&&&&&&&x .:::xX&&&&&&&&&:  .....:X$&$&$$$$$$&&        
                    :           :x+xXXXX$$$$$$XxX&&&&&XxXxXXXXXX$&&&$XXx;:X: .;X&&+.  .+       :&&&&X&&&x+XXXXXxx$.   .X$&&&&&&&&$X;;:.+xxxX&&&&&&&$&&&&&&&&&&$XXX$$&&&&$&&&&&&X.....:+X$$$xXX$$$$&        
                   ...         .:X+++xx  XX$$$$+x&&&&&&&&&$x$&&x+&&&&&$;;:.xX   .   .x+..    ..$&&&;x$&&&xxXxXxXX+   ..+&&&&&&&&&&&&X;;:.;xXxX$$&$$&&&&&&&&&&&&&$;+:+$XX$&&$&&&&$:....;XXXX+XXX$$$$        
                   :          ...+:..;     $$$&::&&&&&&&&&&XX$X++&&&&&&&$   xXX    ..   ++. : &&&&&:+X&&&&X;;;:.       .$&&&&&&&&&&&&&x::. :XxxxX$&&&&&&&&&&&&&&&X:::;X$$x;;$&&&&&:.. ;xXXX$:X$x$$$        
                   .          .  .  .+XX+ ;X$$$  X&&&&&&&&&&+X$+;$&&&&&&&+  :xX$$:     ..      :&&&;$$&&&&&+ .....     .;$$$&&&&&&&&&&&&x:.. ;XxxxXX$&&&&&&&&&&&&  .;+;::+$&&&&&&&&:...xXXX$&X+$Xx$        
                                  : .xXXx xXXx.  ;&&&&&&&&&&X+X+;X&&&&&&:    +X$$$$X         .::.....x&&&&x.x;..X:      .XX$$&&&&&&&&&&&&&+.... ;XXX$XXX$&&&&&&&&  .::;:.:x$$&&&&&&&:..xXXXX$&&xX$X        
                                     +xxx x+:  .;X$&&&&&&&&&&;xx:+&&&&&$    .x .+xX&&&&$   .;+ .  +xX:..+$XX;..$Xx    x  xXX$$$&&&&&&&&&&&&$; .:...:;X$$&$&&&&&&&&&::.....;X$$&&&&&&$:.:XXXX$$&&x$&        
                                      :;.    :xX$$$$&&&&&&&&&$:x::$&&&&&.        ::.:x+X$&:;+&x  xX$X .. .......xx.  .X :X$X$$$$&&&&&&&&&&&&&+  ...;X$$&&&&&&&&&&&&&&+....:+XX$&&&&&&$..:X$$$$&$$$$        
                                           .;xxXXXX$$&&&&&&&&&+:::+&&&&X . ;:    : .:+:;xxX$$&$. .:...:.   ..++xX:;;;;x .XXXX$$$X$&&&&&$&&&&&&x::;x$$&$$&&&&&&&&&&&&&&&:   .+X$&&&&&&&$::+$$$$$$&$$        
                                   :        :;;;++xX$$&&&&&&&&$..::X&&&;   .x  +.  .:::.;;++X$&&&&$Xx.    ..;$$:.:;; X+.;XXXxX$xx$$&&&$x&&&&&&&&$$$&$+xX&$$x+$&&&&&&&&&&X...:+XX$&&&&&&X::x$$$$$$$$        
                                             ..::;+XX$&&&&&&&&&;:.:+x&&$ : :    :.: ;::..:::;;+XX$$&&&&&x   X$X...:  X$$$+.;  ;.xx;;&X+&&&&&&&&&&&&&+x$$$x;;;+$$$&&&&&&&&&+...+X$$$&&&&&X:;x$$$$$&&        
                                             ....:+xX$&&&&&&&&&;..::xx&&&x .    +    X:..+; ;.::;;;;+$$$$&$.x&$$$:    .:xX  X;:..+X$&xX$&&&&&&&&&&&&X..  :::.:x$$$$&&&&&&&&$. ..XXX$$&&&&$+;X$$$$&&        
                                            ..  .:;xX$&&&&&&&&$. ..::;;; .;x        .:XX  .x+::::;x+;;.xx$&&&&&$.   ....; .Xx;   .X$&X$XX$$$$&&&&&&&&X:::x$x. .+X$$$$$&&&&&&$ :X.;XXX$$&&$$$$$$&&&&        
                                                 :+X$$&&&&&&&&+ ...:..:     .xxX.   .:x    +;$X  :;xXX..:+x&&:+&&&&&$$Xx+ ;Xxx+xX$&&&&&XXx;::x&&&&&&&&&&&X;:+;  .+X$X$$&&&&&&&; x+:+XX$$$&$$$$$$&&&        
                                               .;xX$&&&&&&&&&:   + ....x   ;+X&$$  ...+    ;;$;  .:+&x  .;;XX .;X&&x+&$$$:;:$xX$&&&&&&X.:. +x$&&X..$&&&&&&&&&x    :xX$$$$X&&&&&$;X$xx$$$$$&&&&$$&&&        
                                              .;x$&&&&&&&&&&.    X: .:.:  :.. .&&&$.+&&    :;X   :;;$;   :;x;  :x$$$;+$$&&&&&$&&&&&&X.    x$&&$$$.;&&&&&&&&&&&&&; .  +XXX$$X$&&&$$$$+$$$$$$$&&&&&&&        
                                               +X$&&&&&&&&x     ;XX   ::  ;++xx&&&&&&&&&&X;;+$   :;+X:   +:x$...+$&&$$&&&&&&&&$&&&&x     ;$$+:x$:;&&&$&$&&&&&&&&&&x.  .;XXXX$XX$&X$$$$X+;+$$$$&&&&&        
                                          .  ..:x$$&&&&&&       ;;X.  +x.:   ; X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&;+&&&&&&&X.:+&&Xxx..:;X$&;.$$$&&&&&$$$&&X.....xXX$$XX$$&&&&&$$&&&&&&&Xx        
                                            +::.;xX$&&&&:         ::     .   :;.X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$$X:X&&&&&&&&&&&X.    ..;X$x.;$$$$$&$$$$$&&X. .x.+$$$X$$$$$$&&&&$&$&&&&$        
                                             .x;:;xX$&&&&&   :     +     .     ;. &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$&&&&$&&&&&&&&&&&&$$$X:  ..:xX  :$$$XXx$$X$&&&+.:$$x:+XX$$$$&$&&&&$$&$+$$        
                                      :        $+:;x$$&&&&&&;    . +      .::   . ::+&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$;X:;;+&&&&&&&&&&&&&$X&&&&&&&&$:    :   ;x+++++x$$&&x;$$$x:XXX$$&$$&&&$$$x+$$$        
                                                 +;+$$&&&&&&&&&x  .+    .:. .    .   :X$$x&&&&&&&&&&&&&&&&&&&&&&$&&$x++X$:+X&&&&&&&&X&&x$&&&&&&$$$$$XXX:        .;;;xxxXXXXX$&&$$$$$$&$$$&$$X:X$$$$        
                                           .   :+  x$&&&&&&&&&&&&&;       x .:++::  .;x$;   :.X xxxX$X:.::+x    +$x:;+x$$$$&&&&&&&&&x$x&&$$$$$$$XXxxx+; +x;        .;+xxXXXX$$$$&&&&&$$$$&$$X;X$$$$        
                                      .   ;   ..:.  .X&&&&&&&&&&&&&X     .:  .  ...  :x$+  :+XX .;;;x;    +x; .:+$x.;+X&&X+$$$&&&&$&xX&&&$$$$XXXXxx;     ...:+       ...+xXXX$xX$$&&&&&$$$$$&&X+X$$        


                                                        ::::::::::: :::    ::: ::::::::::              :::     :::::::::  :::   :::  ::::::::   :::::::: 
                                                           :+:     :+:    :+: :+:                   :+: :+:   :+:    :+: :+:   :+: :+:    :+: :+:    :+: 
                                                          +:+     +:+    +:+ +:+                  +:+   +:+  +:+    +:+  +:+ +:+  +:+        +:+         
                                                         +#+     +#++:++#++ +#++:++#            +#++:++#++: +#++:++#+    +#++:   +#++:++#++ +#++:++#++   
                                                        +#+     +#+    +#+ +#+                 +#+     +#+ +#+    +#+    +#+           +#+        +#+    
                                                       #+#     #+#    #+# #+#                 #+#     #+# #+#    #+#    #+#    #+#    #+# #+#    #+#     
                                                      ###     ###    ### ##########          ###     ### #########     ###     ########   ########       
                                                                                                                                                                                    
)";

//Short story
const char* story = R"(You are an adventurer in a vast world where dungeons hold untold treasures and unspeakable horrors. For years, whispers have circulated about the Abyss dungeon, a place where 

the earth itself seems to tremble, and the very darkness devours all light. No one has ever returned from its depths, but that has never stopped those daring enough to seek glory and power.

You've trained for this moment your entire life, honing your skills as a warrior, mastering the use of Divine Art, and preparing to face whatever the Abyss throws at you.

Your goal is simple: Enter the dungeon, face its horrors, and slay the Overlord an ancient being so powerful that even the gods tremble in fear at the thought of it.

You stand before the entrance, the dungeon great stone door slowly creaks open, as if it has been waiting for you. The air is thick with the scent of decay and an unnatural chill hangs in the air.       )";

//The Overlord speaks
const char* bossSpeak = R"(Foolish mortal, you think your light will save you? It will flicker and die, just like the others.)";

//Player dialog
const char* playerWin = R"(The light will never die, and neither will I.)";