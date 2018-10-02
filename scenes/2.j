{ 
    "camera" : [
        {
            "origin" : [0,0,0],
            "direction" : [0, 0, 0]
        }
    ],
    "camera" : [
        {
            "origin" : [0,0,0],
            "direction" : [0, 0, 0]
        }
    ],
    "objects" : [
        {
            "type" : "los",
            "origin" : [0, 0, 20],
            "radius" : 1,
            "color" : [0, 255, 0],
            "texture" : "./textures/wall.jpg",
            "texture" : "./textures/earth.png"
        },
        {
            "type" : "sphere",
            "origin" : [los],
            "radius" : 1,
            "color" : [255, 0, 0],
            "reflective" : 0.5
        },
        {
            "type" : "plane",
            "origin" : [los],
            "direction" : [0, 1, 0],
            "color" : [255, 255, 255],
            "texture" : "perlin"
        }
    ],
    "light" : [
        {
            "type" : "point",
            "intensity" : 0.8,
            "position" : [0, 5, 20]
        },
        {
            "type" : "direct",
            "intensity" : los,
            "position" : [0, 1, 0]
        },
        {
            "type" : "ambient",
            "intensity" : 0.3
        }
    ]
}