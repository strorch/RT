{
  "camera" : [
    {
      "origin" : [0, 0, -96],
      "direction" : [0, 0, 0]
    }
  ],

  "light" : [
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [0, 9, 0]
    }
  ],

  "objects" : [
    {
      "type" : "plane",
      "origin" : [0,-15,0],
      "direction" : [0, 1, 0],
      "color" : [192,192,192],
    },
    {
      "type" : "plane",
      "origin" : [0,15,0],
      "direction" : [0, -1, 0],
      "color" : [192,192,192]
    },

    {
      "type" : "2sheet_hyperboloid",
      "origin" : [0,0,36],
      "radius" : 3,
      "color" : [255,192,0],
      "reflective" : 0.15
    },
    {
      "type" : "sphere",
      "origin" : [0,0,36],
      "radius" : 3,
      "color" : [255,255,255],
      "texture" : "textures/earth.png"
    },
    {
      "type" : "paraboloid",
      "origin" : [-3.8,0,36],
      "direction" : [-1, 0, 0],
      "cap" : 100,
      "color" : [255,192,0],
      "reflective" : 0.15
    },
    {
      "type" : "paraboloid",
      "origin" : [3.8,0,36],
      "direction" : [1, 0, 0],
      "cap" : 100,
      "color" : [255,192,0],
      "reflective" : 0.15
    },

    {
      "type" : "2sheet_hyperboloid",
      "origin" : [-36,0,0],
      "radius" : 0.3,
      "color" : [255,192,0],
      "reflective" : 0.15
    },
    {
      "type" : "sphere",
      "origin" : [-36,0,0],
      "radius" : 0.3,
      "color" : [255,255,255],
      "reflective" : 0.15
    },
    {
      "type" : "paraboloid",
      "origin" : [-36,0,-0.8],
      "direction" : [0, 0, -1],
      "cap" : 100,
      "color" : [255,192,0],
      "reflective" : 0.15
    },
    {
      "type" : "paraboloid",
      "origin" : [-36,0,0.8],
      "direction" : [0, 0, 1],
      "cap" : 100,
      "color" : [255,192,0],
      "reflective" : 0.15
    },

    {
      "type" : "2sheet_hyperboloid",
      "origin" : [36,0,0],
      "radius" : 0.3,
      "color" : [255,192,0],
      "reflective" : 0.15
    },
    {
      "type" : "sphere",
      "origin" : [36,0,0],
      "radius" : 0.3,
      "color" : [255,255,255],
      "reflective" : 0.15
    },
    {
      "type" : "paraboloid",
      "origin" : [36,0,-0.8],
      "direction" : [0, 0, -1],
      "cap" : 100,
      "color" : [255,192,0],
      "reflective" : 0.15
    },
    {
      "type" : "paraboloid",
      "origin" : [36,0,0.8],
      "direction" : [0, 0, 1],
      "cap" : 100,
      "color" : [255,192,0],
      "reflective" : 0.15
    },

  ],

}
