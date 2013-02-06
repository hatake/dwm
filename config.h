#define NUMCOLORS 4
#define MODKEY Mod1Mask
#define MONKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,			KEY, view, {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,	KEY, tag,  {.ui = 1 << TAG} },


static const char colors[NUMCOLORS][ColLast][9] = {
	/* border	foreground	background */
	{ "#222222", "#999999", "#222222" },                // 1 = normal
	{ "#999999", "#DCDCDC", "#999999" },                // 2 = selected
	{ "#222222", "#DCDCDC", "#222222" },  				// 3 = urgent
	{ "#222222", "#DCDCDC", "#222222" },  				// 4 = occupied
};

static const char font[]			        = "Liberation Mono:Regular:size=10:antialias=true:hinting=true";
static const unsigned int systrayspacing	= 1;	    // Systray spacing
static const unsigned int borderpx			= 1;	    // Border pixel of windows
static const unsigned int gappx				= 6;	    // Gap pixel between windows
static const unsigned int snap				= 2;	    // Snap pixel
static const Bool showbar					= True;	    // False means no bar
static const Bool showsystray				= True;	    // False means no systray
static const Bool topbar					= True;	    // False means bottom bar
static const float mfact		            = 0.60;     // factor of master area size [0.05..0.95]
static const int nmaster 		            = 1;        // number of clients in master area
static const Bool resizehints	            = False;    // True means respect size hints in tiled resizals
static const float opacity 					= 0.00;

static const Layout layouts[] = {
	/* symbol			gaps		arrange */
	{ "  [T]",     	True,	    tile	},
	{ "  [B]",     	True,	    bstack	},
	{ "  [M]",     	False,	    monocle	},
	{ "  [F]",		False,	    NULL	},
};

static const Tag tags[] = {
	/* name		layout          mfact       nmaster */
	{ " web ",	&layouts[0],        -1,		    -1 },
	{ " chat ",	&layouts[0],        -1,		    -1 },
	{ " term ",	&layouts[0],        -1,		    -1 },
	{ " media ",&layouts[0],        -1,			-1 },
	{ " code ",	&layouts[0],        -1,		    -1 },
	{ " misc ",	&layouts[0],        -1,		    -1 },
};

static const Rule rules[] = {
	/*WM_CLASS		WM_CLASS	WM_NAME
	  class			instance	title				tags mask	isfloating	monitor */
	{ "chromium",	NULL,		NULL,				1,			False,		-1 },
	{ "skype",		NULL,		NULL,				1 << 1,		False,		-1 },
};

static const char *menu[]   = { "dmenu_run", "-p", "package:", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *term[]   = { "urxvtc", NULL };
static const char *file[]   = { "thunar", NULL };
static const char *edit[]   = { "geany", NULL };
static const char *webb[]   = { "chromium", NULL };
//static const char *chat[]   = { "skype", NULL };
//static const char *ircc[]   = { "urxvtc", "-e", "irssi" };
//static const char *musc[]   = { "urxvtc", "-e", "mocp" };
static const char *volu[]   = { "amixer", "-q", "sset", "Master", "5%+", "unmute", NULL };
static const char *vold[]	= { "amixer", "-q", "sset", "Master", "5%-", "unmute", NULL };
static const char *volm[]	= { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *play[]	= { "mocp", "--toggle-pause", NULL };
static const char *prev[]	= { "mocp", "--previous", NULL };
static const char *next[]	= { "mocp", "--next", NULL };
static const char *stop[]	= { "mocp", "--stop", NULL };

static Key keys[] = {
	/* modifier					key				 			function		argument */
	{ MONKEY,		            XK_p,						spawn,          {.v = menu} },
	{ MONKEY,		    		XK_Return,					spawn,          {.v = term} },
	{ MONKEY,		            XK_f,						spawn,          {.v = file} },
	{ MONKEY,		            XK_e,						spawn,          {.v = edit} },
	{ MONKEY,		            XK_w,						spawn,          {.v = webb} },

	{ MONKEY,		            XK_F5,						spawn,          {.v = play} },
	{ MONKEY,		    		XK_F6,						spawn,          {.v = stop} },
	{ MONKEY,		            XK_F7,						spawn,          {.v = prev} },
	{ MONKEY,		            XK_F8,						spawn,          {.v = next} },
	{ MONKEY,		            XK_F10,						spawn,          {.v = mute} },
	{ MONKEY,		            XK_F11,						spawn,          {.v = vold} },
	{ MONKEY,		    		XK_F12,						spawn,          {.v = volu} },

    { MODKEY|ShiftMask,			XK_q,						quit,			{0} },
	{ MODKEY|ShiftMask,			XK_c,						killclient,		{0} },

	{ MODKEY|ControlMask,		XK_b,						togglebar,		{0} },
	{ MODKEY|ShiftMask,			XK_f,						togglefloating,	{0} },
	{ MODKEY,					XK_space,					setlayout,		{0} },

	{ MODKEY,					XK_Right,					focusstack,		{.i = +1 } },
	{ MODKEY,					XK_Left,					focusstack,		{.i = -1 } },

	{ MONKEY,					XK_Left,					focusmon,		{.i = -1 } },
	{ MONKEY,					XK_Right,					focusmon,		{.i = +1 } },

	{ MONKEY|ShiftMask,			XK_Left,					tagmon,			{.i = -1 } },
	{ MONKEY|ShiftMask,			XK_Right,					tagmon,			{.i = +1 } },

	{ MODKEY,					XK_Return,					zoom,			{0} },
	{ MODKEY,					XK_Tab,						view,			{0} },

	{ MODKEY,					XK_bracketleft,				setmfact,		{.f = -0.05} },
	{ MODKEY,					XK_bracketright,			setmfact,		{.f = +0.05} },
	{ MODKEY,					XK_equal,					incnmaster,		{.i = +1 } },
	{ MODKEY,					XK_minus,					incnmaster,		{.i = -1 } },

	{ MODKEY,					XK_t,						setlayout,		{.v = &layouts[0] } },
	{ MODKEY,					XK_b,						setlayout,		{.v = &layouts[1] } },
	{ MODKEY,					XK_m,						setlayout,		{.v = &layouts[2] } },
	{ MODKEY,					XK_f,						setlayout,		{.v = &layouts[3] } },
	{ MODKEY,					XK_o,						view,			{.ui = ~0 } },
	{ MODKEY|ShiftMask,			XK_a,						tag,			{.ui = ~0 } },

	TAGKEYS(					XK_1,						0)
	TAGKEYS(					XK_2,						1)
	TAGKEYS(					XK_3,						2)
	TAGKEYS(					XK_4,						3)
	TAGKEYS(					XK_5,						4)
	TAGKEYS(					XK_6,						5)
};

/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click			event mask	button		function		argument */
	{ ClkLtSymbol,		0,			Button1,	setlayout,		{0} },
	{ ClkLtSymbol,		0,			Button3,	setlayout,		{.v = &layouts[4]} },
	{ ClkStatusText,	0,			Button2,	spawn,			{.v = term } },
	{ ClkClientWin,		MODKEY,		Button1,	movemouse,		{0} },
	{ ClkClientWin,		MODKEY,		Button2,	togglefloating,	{0} },
	{ ClkClientWin,		MODKEY,		Button3,	resizemouse,	{0} },
	{ ClkTagBar,		0,			Button1,	view,			{0} },
	{ ClkTagBar,		MODKEY,		Button1,	tag,			{0} },
};
