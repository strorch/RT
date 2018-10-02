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
      "origin" : [-2, 0, 20],
      "radius" : 1,
      "color" : [255, 0, 0],
      "texture" : "./textures/waller.jpg"
    },
    {
      "type" : "sphere",
      "origin" : [0, 0, 20],
      "radius" : 1,
      "color" : [255, 0, 255],
      "texture" : "chessboard"
    },
    {
      "type" : "sphere",
      "origin" : [2, 0, 20],
      "radius" : 1,
      "color" : [255, 255, 0],
      "texture" : "perlin"
    },
    {
      "type" : "sphere",
      "origin" : [0, 2, 20],
      "radius" : 1,
      "color" : [1000, 1000, 1000]
    },
    {
      "type" : "sphere",
      "origin" : [2, 2, 20],
      "radius" : 1,
      "color" : [255, 255, 0],
      "texture" : "./textures/earth.png"
    },
    {
      "type" : "sphere",
      "origin" : [-2, 2, 20],
      "radius" : 1,
      "color" : [255, 255, 0],
      "texture" : "chessboard"
    },
    {
      "type" : "sphere",
      "origin" : [0, -2, 20],
      "radius" : 1,
      "color" : [255, 255, 0],
      "texture" : "./textures/pustynia.jpg"
    },
    {
      "type" : "sphere",
      "origin" : [2, -2, 20],
      "radius" : 1,
      "color" : [255, 255, 0],
      "texture" : "./textures/pustynia.jpg"
    },
    {
      "type" : "sphere",
      "origin" : [-2, -2, 20],
      "radius" : 1,
      "color" : [255, 255, 0],
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
      "type" : "point",
      "intensity" : 0.8,
      "position" : [-2, 5, 20]
    },
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [-2, -5, 20]
    },
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [-2, 0, -20]
    }
  ]
}
