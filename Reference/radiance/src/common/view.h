/* RCSid $Id: view.h,v 2.8 2003/02/25 02:47:22 greg Exp $ */
/*
 *  view.h - header file for image generation.
 *
 *  Include after fvect.h
 *  Includes resolu.h
 */

#include "copyright.h"

#include  "resolu.h"

				/* view types */
#define  VT_PER		'v'		/* perspective */
#define  VT_PAR		'l'		/* parallel */
#define  VT_ANG		'a'		/* angular fisheye */
#define  VT_HEM		'h'		/* hemispherical fisheye */
#define  VT_CYL		'c'		/* cylindrical panorama */

typedef struct {
	int  type;		/* view type */
	FVECT  vp;		/* view origin */
	FVECT  vdir;		/* view direction */
	FVECT  vup;		/* view up */
	double  horiz;		/* horizontal view size */
	double  vert;		/* vertical view size */
	double  hoff;		/* horizontal image offset */
	double  voff;		/* vertical image offset */
	double  vfore;		/* fore clipping plane */
	double  vaft;		/* aft clipping plane (<=0 for inf) */
	FVECT  hvec;		/* computed horizontal image vector */
	FVECT  vvec;		/* computed vertical image vector */
	double  hn2;		/* DOT(hvec,hvec) */
	double  vn2;		/* DOT(vvec,vvec) */
} VIEW;			/* view parameters */

extern VIEW  stdview;

#define  viewaspect(v)	sqrt((v)->vn2/(v)->hn2)

#define  STDVIEW	{VT_PER,{0.,0.,0.},{0.,1.,0.},{0.,0.,1.}, \
				45.,45.,0.,0.,0.,0., \
				{0.,0.,0.},{0.,0.,0.},0.,0.}

#define  VIEWSTR	"VIEW="
#define  VIEWSTRL	5

#ifdef NOPROTO

extern char	*setview();
extern void	normaspect();
extern double	viewray();
extern void	viewloc();
extern void	pix2loc();
extern void	loc2pix();
extern int	getviewopt();
extern int	sscanview();
extern void	fprintview();
extern char	*viewopt();
extern int	isview();
extern int	viewfile();

#else

extern char	*setview(VIEW *v);
extern void	normaspect(double va, double *ap, int *xp, int *yp);
extern double	viewray(FVECT orig, FVECT direc, VIEW *v, double x, double y);
extern void	viewloc(FVECT ip, VIEW *v, FVECT p);
extern void	pix2loc(FLOAT loc[2], RESOLU *rp, int px, int py);
extern void	loc2pix(int pp[2], RESOLU *rp, double lx, double ly);
extern int	getviewopt(VIEW *v, int ac, char *av[]);
extern int	sscanview(VIEW *vp, char *s);
extern void	fprintview(VIEW *vp, FILE *fp);
extern char	*viewopt(VIEW *vp);
extern int	isview(char *s);
extern int	viewfile(char *fname, VIEW *vp, RESOLU *rp);

#endif