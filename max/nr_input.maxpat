{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 5,
			"minor" : 1,
			"revision" : 9
		}
,
		"rect" : [ 2046.0, 113.0, 188.0, 580.0 ],
		"bglocked" : 0,
		"defrect" : [ 2046.0, 113.0, 188.0, 580.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 8.0, 8.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "umenu",
					"presentation_rect" : [ 176.0, 48.0, 100.0, 20.0 ],
					"items" : [ "from_noise_rhythm_1", ",", "to MaxMSP 1", ",", "to MaxMSP 2" ],
					"numinlets" : 1,
					"types" : [  ],
					"patching_rect" : [ 224.0, 134.0, 100.0, 20.0 ],
					"numoutlets" : 3,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-23",
					"outlettype" : [ "int", "", "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "0",
					"presentation_rect" : [ 240.0, 18.0, 32.5, 18.0 ],
					"numinlets" : 2,
					"patching_rect" : [ 259.0, 64.0, 32.5, 18.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-22",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "midiinfo",
					"presentation_rect" : [ 176.0, 15.0, 52.0, 20.0 ],
					"numinlets" : 2,
					"patching_rect" : [ 224.0, 101.0, 52.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-20",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s midi_port",
					"presentation_rect" : [ 176.0, 78.0, 69.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 224.0, 164.0, 69.0, 20.0 ],
					"numoutlets" : 0,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-19",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"presentation_rect" : [ 24.0, 464.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 565.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"id" : "obj-17",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "midi_input 8",
					"presentation_rect" : [ 56.0, 464.0, 75.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 536.0, 75.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-18",
					"outlettype" : [ "int" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"presentation_rect" : [ 24.0, 400.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 505.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"id" : "obj-15",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "midi_input 7",
					"presentation_rect" : [ 56.0, 400.0, 75.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 476.0, 75.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-16",
					"outlettype" : [ "int" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"presentation_rect" : [ 25.0, 333.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 425.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"id" : "obj-13",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "midi_input 6",
					"presentation_rect" : [ 56.0, 336.0, 75.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 396.0, 75.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-14",
					"outlettype" : [ "int" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"presentation_rect" : [ 24.0, 272.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 370.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"id" : "obj-11",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "midi_input 5",
					"presentation_rect" : [ 56.0, 272.0, 75.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 41.0, 338.0, 75.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-12",
					"outlettype" : [ "int" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"presentation_rect" : [ 24.0, 200.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 300.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"id" : "obj-9",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "midi_input 4",
					"presentation_rect" : [ 56.0, 200.0, 75.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 271.0, 75.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-10",
					"outlettype" : [ "int" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"presentation_rect" : [ 24.0, 136.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 233.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"id" : "obj-7",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "midi_input 3",
					"presentation_rect" : [ 56.0, 136.0, 75.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 204.0, 75.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-8",
					"outlettype" : [ "int" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"presentation_rect" : [ 24.0, 72.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 162.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"id" : "obj-5",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "midi_input 2",
					"presentation_rect" : [ 56.0, 72.0, 75.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 133.0, 75.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-6",
					"outlettype" : [ "int" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"presentation_rect" : [ 24.0, 8.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 96.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"id" : "obj-4",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "midi_input 1",
					"presentation_rect" : [ 56.0, 8.0, 75.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 40.0, 67.0, 75.0, 20.0 ],
					"numoutlets" : 1,
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-1",
					"outlettype" : [ "int" ],
					"fontsize" : 12.0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 1 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-20", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
