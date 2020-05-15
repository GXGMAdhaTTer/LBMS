void HSL2RGB(double h, double sl, double l, double* r, double* g, double* b)
{
	double v;

	v = (l <= 0.5) ? (l * (1.0 + sl)) : (l + sl - l * sl);
	if (v <= 0) {
		*r = *g = *b = 0.0;
	}
	else {
		double m;
		double sv;
		int sextant;
		double fract, vsf, mid1, mid2;
		m = l + l - v;
		sv = (v - m) / v;
		h *= 6.0;
		sextant = (int)h;
		fract = h - sextant;
		vsf = v * sv * fract;
		mid1 = m + vsf;
		mid2 = v - vsf;
		switch (sextant) {
		case 0: *r = v; *g = mid1; *b = m; break;
		case 1: *r = mid2; *g = v; *b = m; break;
		case 2: *r = m; *g = v; *b = mid1; break;
		case 3: *r = m; *g = mid2; *b = v; break;
		case 4: *r = mid1; *g = m; *b = v; break;
		case 5: *r = v; *g = m; *b = mid2; break;
		}
	}
}