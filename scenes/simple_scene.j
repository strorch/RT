{
  "camera" : [
    {
      "origin" : [0,0,0],
      "direction" : [0, 0, 0]
    }
  ],

  "objects" : [
    {
      "type" : "sphere",
      "origin" : [0, 0, 20],
      "radius" : 1,
      "color" : [255, 0, 0],
      "reflective" : 0,
      "texture" : "perlin"
    },
    {
      "type" : "sphere",
      "origin" : [-2, 0, 20],
      "radius" : 1,
      "color" : [255, 0, 0],
      "refractive" : 1,
      "texture" : "chessboard"
    },
    {
      "type" : "sphere",
      "origin" : [2, 0, 20],
      "radius" : 1,
      "color" : [255, 0, 0],
      "reflective" : 1
    },
    {
      "type" : "plane",
      "origin" : [2, -2, 20],
      "direction" : [0, 1, -0.1],
      "color" : [255, 255, 0],
      "reflective" : 0
    },
    {
      "type" : "plane",
      "origin" : [2, -2, 20],
      "direction" : [0, -1, 0.1],
      "color" : [255, 0, 0],
      "reflective" : 0
    }
  ],

  "light" : [
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [0, 1, 15]
    }
  ]
}

