# graphics-project
Project &amp; Porfolio IV: Graphics II Course Project

Themes:
Space Theme - Earth/Venus/Mars Orbiting Origin, Moon Orbiting Earth

Camera Controls:
WASD - FORWARD/LEFT/BACK/RIGHT
RIGHT MOUSE CLICK + CURSOR - ROTATE
Q/E - UP/DOWN
Z - ZOOM IN (FOV)
X - ZOOM OUT (FOV)
C - RESET FOV
V - INC NearZ    -- CLIPPING
B - INC FarZ
N - RESET NearZ/FarZ

Lights:  ** All lights use specular lighting (half vector method) **
Keys to place lights (Dynamic Position)
1 - Point
2 - Spot

Directional - Always On (WHITE)
Point - Always On (GREEN)
Spot - Always On (WHITE) - Turned off rotating, can still be moved with 2 key

Geometry:
Stonehedge - uses Obj2Header for complex mesh header and draw
Floor/Talon Shaceship - FBX Loader (Importer.h)

Instancing:
Moons(4, redish textured) are using DrawIndexedInstanced()

Geometery Shader:
Procedurely generated using a point to generate a Green Triang (front center on platform)

Multiple Viewports:
Splitscreen - left camera can move and use light placement
            - right camera is fixed 

Unique Pixel Shader (Modified UV's based on time and wave)
- Applied to Venus Planet
- Applied to the Sun

Unique Vertex Shader (Modified Position based on cosine wave)
- Applied to Spaceship *** It's warped leaning side to side using cosine and hovering IN the vertex shader *** (Talked with you about this yesterday and said to leave a comment)