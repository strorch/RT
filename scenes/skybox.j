{
  "camera" : [
    {
      "origin" : [0,0,2.5],
      "direction" : [0, 0, 0]
    }
  ],

  "objects" : [
    {
      "type" : "sphere",
      "origin" : [0, 0, 0],
      "radius" : 50,
      "color" : [255, 0, 0],
      "texture" : "./textures/sky.jpg"
    },
    {
      "type" : "sphere",
      "origin" : [0, 0, 10],
      "radius" : 1,
      "color" : [255, 255, 255],
	  "reflective" : 1
    },
	{
		"type" : "plane",
		"origin" : [0, -1, 0],
		"direction" : [0, 1, 0],
		"color" : [255, 255, 255],
		"texture" : "./textures/grass.png"
	}
  ],

  "light" : [
    {
      "type" : "point",
      "intensity" : 0.8,
      "position" : [0, 10, 0]
    }
  ]
}
