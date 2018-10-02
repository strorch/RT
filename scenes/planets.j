{
  "camera" : [
    {
      "origin" : [0,0,-40],
      "direction" : [0, 0, 0]
    }
  ],

  "objects" : [
    {
      "type" : "sphere",
      "origin" : [0, 0, 30],
      "radius" : 2,
      "color" : [255, 0, 0],
      "texture" : "./textures/earth.png"
    },
    {
      "type" : "sphere",
      "origin" : [-1.5, 2.5, 25],
      "radius" : 0.3,
      "color" : [255, 0, 0],
      "texture" : "./textures/moon.jpeg"
    },
    {
      "type" : "sphere",
      "origin" : [5, -4, 80],
      "radius" : 15,
      "color" : [255, 0, 0],
	  "texture" : "perlin"
    },
    {
      "type" : "sphere",
      "origin" : [-2, -1, 25],
      "radius" : 1,
      "color" : [255, 0, 0],
	  "texture" : "./textures/mars.png"
    }
	{
		"type" : "disk",
      	"origin" : [5, -4, 80],
		"direction" : [3.2, -37, 10],
      	"radius" : 500,
      	"color" : [173, 105, 15],
	}
  ],

  "light" : [
    {
      "type" : "point",
      "intensity" : 1,
      "position" : [-3, 5, 22]
    }
  ]
}
