#ifndef _MYGL_H_
#define _MYGL_H_

#define PI 3.14159265

#include "definitions.h"
#include "stdio.h"
#include "math.h"

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************


/*
    Representa uma cor.
*/
struct Color
{
    unsigned char r, g, b, a;
};

/*
    Representa um ponto.
*/
struct Point
{
    int x, y;
};

/*
    Representa o par ponto-cor.
*/
struct ColoredPoint
{
    Point p;
    Color c;
};

/*
    Representa uma reta definida por dois pares cor-ponto.
*/
struct Line
{
    ColoredPoint p0;
    ColoredPoint p1;
};

/*
    Representa um triângulo definido por três pares cor-ponto.
*/
struct Triangle
{
    ColoredPoint a0;
    ColoredPoint a1;
    ColoredPoint a2;
};







/*
    Insere um pixel na tela.
*/
void PutPixel(ColoredPoint cp)
{
    // Calculamos o offset do pixel
    unsigned int offset = 4*cp.p.x + 4*cp.p.y*IMAGE_WIDTH;

    // Preenchemos com as cores adequadas.
    FBptr[offset] = cp.c.r; // RED
    FBptr[offset + 1] = cp.c.g; // GREEN
    FBptr[offset + 2] = cp.c.b; // BLUE
    FBptr[offset + 3] = cp.c.a; // ALPHA
}






/*
    Insere um pixel na tela, calculando sua transparência em relação ao pixel já desenhado.
*/
void PutPixelAlpha(ColoredPoint cp)
{
    // Calculamos o offset do pixel
    unsigned int i, offset = 4*cp.p.x + 4*cp.p.y*IMAGE_WIDTH;

    // Preenchemos com as cores adequadas.
    short aux,
        a = (short)cp.c.a,
        colors[] = { (short)cp.c.r, (short)cp.c.g, (short)cp.c.b};
    for (i = 0; i < 3; i++) // Preenchemos cada cor RGB calculando a transparência de acordo com o pixel que já está na tela.
    {
        aux = (short)FBptr[offset + i];
        FBptr[offset + i] = (unsigned char)( (colors[i] - aux)*a/255 + aux );
    }
    FBptr[offset + 3] = cp.c.a;
}





void DrawLineT(Line l, int fillTriangle, ColoredPoint TrianglePoint);

/*
    Desenha uma linha na tela por meio do algoritmo de Bresenham.
*/
void DrawLine(Line l)
{
    ColoredPoint t;
    DrawLineT(l, 0, t);
}

/*
    Desenha uma linha na tela por meio do algoritmo de Bresenham.
*/
void DrawLineT(Line l, int fillTriangle, ColoredPoint TrianglePoint)
{
    // Usamos ponteiros para facilitar a troca de coordenadas/octantes/quadrantes.
    int *x0 = &l.p0.p.x,
        *y0 = &l.p0.p.y,
        *x1 = &l.p1.p.x,
        *y1 = &l.p1.p.y,
        dx = (int)*x1 - (int)*x0, // Diferença não-absoluta de X
        dy = (int)*y1 - (int)*y0, // Diferença não-absoluta de Y
        xmult = 1, // Variável de multiplicação do eixo X, facilita na troca de octantes.
        ymult = 1, // Variável de multiplicação do eixo Y, facilita na troca de octantes.
        thirdqdr = *y0 >= *y1 && *x0 >= *x1; // Terceiro quadrante.



    /**********************************************
     * TROCA DE COORDENADAS, QUADRANTES, OCTANTES
    **********************************************/
    
    if (thirdqdr || dx > 0 && dy < 0) // 3 ou 4 quadrante
    {
        ymult = -1; // Multiplicamos Y por -1 para inverter o eixo.
        l.p0.p.y *= -1; // As coordenadas de Y agora estão negativas; quando os pixels precisarem ser preenchidos,
        l.p1.p.y *= -1; // mudaremos novamente sua grandeza.
    }

    if (thirdqdr || dx < 0 && dy > 0) // O Mesmo para o 2 ou 3 quadrante, desta vez com X
    {
        xmult = -1;
        l.p0.p.x *= -1;
        l.p1.p.x *= -1;
    }

    // Até agora as transformações feitas levaram os quadrantes 2, 3 e 4 a uma equivalência com o quadrante 1.
    // Aqui, transforma-se o segundo octante no primeiro, e por consequência, todo o resto pendente.
    if (abs((int)*y1 - (int)*y0) > abs((int)*x1 - (int)*x0))
    {
        x0 = &l.p0.p.y;
        y0 = &l.p0.p.x;
        x1 = &l.p1.p.y;
        y1 = &l.p1.p.x;
    }


    
    /**********************************************
     * DEFINIÇÕES DAS VARIÁVEIS
    **********************************************/

    dx = abs((int)*x1 - (int)*x0); // re-calculamos Delta X e Y
    dy = abs((int)*y1 - (int)*y0);

    int d_e = dy, // Acréscimo inferior.
        d_ne = dy - dx, // Acréscimo superior.
        d = 2*dy - dx, // Valor de 'd' para o primeiro ponto.
        color_deltar = ((int)l.p1.c.r - (int)l.p0.c.r), // Diferença da cor vermelha entre os dois pontos.
        color_deltag = ((int)l.p1.c.g - (int)l.p0.c.g), // Diferença da cor verde entre os dois pontos.
        color_deltab = ((int)l.p1.c.b - (int)l.p0.c.b), // Diferença da cor azul entre os dois pontos.
        i = 1; // Contador do loop. Usado na interpolação de cores.
    

    l.p1.c = l.p0.c; // Guardados as diferenças em cada componente de cor,
    //re-utilizaremos uma das variáveis para guardar o valor inicial e a outra para fazer os acréscimos.



    
    /**********************************************
     * APLICAÇÃO DO ALGORITMO
    **********************************************/

    l.p0.p.x *= xmult; // Aplicamos as transformações nos eixos X-Y
    l.p0.p.y *= ymult;
    PutPixel(l.p0);    // Desenhamos o primeiro pixel.
    l.p0.p.x *= xmult; // Desfazemos-as.
    l.p0.p.y *= ymult;
    

    // Percorremos *x0 até *x1; note que essas variáveis podem estar, na verdade, apontando para o eixo Y.
    for ((*x0)++; *x0 <= *x1; (*x0)++)
    {
        if (d < 0) // Se d < 0, então o próximo ponto está no mesmo y que o anterior.
        {
            d += d_e;
        }
        else // Senão, está um pixel acima (y) que o anterior.
        {
            (*y0)++; // Incrementamos o y
            d += d_ne;
        }
        

        // Calculamos a interpolação das cores. Por se tratar de inteiros, foi decidido manter a expressão completa,
        // com os produtos, divisões e somas calculados em cada instante, com o propósito de aumentar a precisão.
        l.p0.c.r = (unsigned char)(i*color_deltar/dx + l.p1.c.r);
        l.p0.c.g = (unsigned char)(i*color_deltag/dx + l.p1.c.g);
        l.p0.c.b = (unsigned char)(i*color_deltab/dx + l.p1.c.b);
        // printf("Das war einfach\n");
        i++; // Incrementamos o contador do loop.

        l.p0.p.x *= xmult; // Aplicamos as transformações nos eixos X-Y
        l.p0.p.y *= ymult;

        if (fillTriangle)
        {
            Line nline;
            nline.p0 = l.p0;
            nline.p1 = TrianglePoint;
            DrawLine(nline);
        }

        PutPixel(l.p0);    // Desenhamos o pixel correspondente.
        l.p0.p.x *= xmult; // Desfazemos-as.
        l.p0.p.y *= ymult;
    }
}






/*
    Desenha um triângulo na tela.
*/
void DrawTriangle(Triangle t)
{
    // Para cada aresta, definimos uma reta entre os pontos e desenhamos sua linha.
    Line l; // Variável auxiliar.

    l.p0 = t.a0;
    l.p1 = t.a1;
    DrawLine(l);

    l.p0 = t.a1;
    l.p1 = t.a2;
    DrawLine(l);
    
    l.p0 = t.a2;
    l.p1 = t.a0;
    DrawLine(l);
}


/*
    Desenha um triângulo preenchido na tela.
*/
void DrawAndFillTriangle(Triangle t)
{
    // Para cada aresta, definimos uma reta entre os pontos e desenhamos sua linha.
    Line l; // Variável auxiliar.

    l.p0 = t.a0;
    l.p1 = t.a1;
    DrawLineT(l, 1, t.a2);

    l.p0 = t.a1;
    l.p1 = t.a2;
    DrawLineT(l, 1, t.a0);
    
    l.p0 = t.a2;
    l.p1 = t.a0;
    DrawLineT(l, 1, t.a1);
}











    
/**********************************************
 * EXEMPLOS PRONTOS
**********************************************/


/*
    Desenha uma espécie de asterisco. Quanto maior o argumento, maior a quantidade de retas.
*/ 
void Example_Asterisk(int div)
{
	int gpp = 255 / div;
	Line l;

	l.p0.p.x = IMAGE_WIDTH / 2; // Os pontos iniciais são o centro do quadro.
	l.p0.p.y = IMAGE_HEIGHT / 2;

	l.p0.c.r = 0;
	l.p0.c.g = 255;
	l.p0.c.b = 255;
	l.p0.c.a = 255;

	l.p1.c.r = 255;
	l.p1.c.g = 0;
	l.p1.c.b = 0;
	l.p1.c.a = 255;


	unsigned char *rr = &l.p0.c.g;

	float i = 0;
	for (; i <= 2*PI; i += PI / div) // Percorre uma circuferência.
	{
		l.p1.p.x = l.p0.p.x + (int)(sin(i) * (float)(4*IMAGE_HEIGHT / 9));
		l.p1.p.y = l.p0.p.y + (int)(cos(i) * (float)(4*IMAGE_HEIGHT / 9));
		(*rr)--;
		if (l.p0.c.g == 250)
		{
			rr = &l.p0.c.b;
		}

		DrawLine(l);
		//PutPixelStruct(p1, r);
	}
}



/*
    Preenche o background. Para cada valor no argumento, desenha uma reta de um ponto a outro.
*/ 
void Example_Slide(int delta)
{
	Line l0, l1; // Desenhamos duas retas. Cada uma liga uma extremidade do quadro ao centro do mesmo.
    // Ambas desenham as retas com interpolação, tal que o centro é verde. A outra extremidade é azul ou vermelho.

	l0.p1.c.r = l1.p0.c.r = 0;
	l0.p1.c.g = l1.p0.c.g = 255;
	l0.p1.c.b = l1.p0.c.b = 0;
	l0.p1.c.a = l1.p0.c.a = 255;

    l0.p1.p.x = l1.p0.p.x = IMAGE_WIDTH / 2;
    l0.p1.p.y = l1.p0.p.y = IMAGE_HEIGHT / 2;


	l0.p0.c.r = 255;
	l0.p0.c.g = 0;
	l0.p0.c.b = 0;
	l0.p0.c.a = 255;

	l1.p1.c.r = 0;
	l1.p1.c.g = 0;
	l1.p1.c.b = 255;
	l1.p1.c.a = 255;

    // Usamos os ponteiros para escrever menos.
    int sumsize = IMAGE_HEIGHT+IMAGE_WIDTH, scnqdrt = (delta % (2*sumsize)) < sumsize,
        *x0 = scnqdrt ? &l0.p0.p.x : &l1.p1.p.x,
        *y0 = scnqdrt ? &l0.p0.p.y : &l1.p1.p.y,
        *x1 = scnqdrt ? &l1.p1.p.x : &l0.p0.p.x,
        *y1 = scnqdrt ? &l1.p1.p.y : &l0.p0.p.y;
    
    if (delta % sumsize < IMAGE_WIDTH) // De -45 a 45 graus OU sua inversa.
    {
        *x0 = delta % sumsize;
        *y0 = 0;
        *x1 = IMAGE_WIDTH - 1 - *x0;
        *y1 = IMAGE_HEIGHT - 1;
    }
    else // De 45 a 135 graus OU sua inversa.
    {
        *x0 = IMAGE_WIDTH - 1;
        *y0 = (delta % sumsize) - IMAGE_WIDTH;
        *x1 = 0;
        *y1 = IMAGE_HEIGHT - 1 - *y0;
    }

    DrawLine(l0);
    DrawLine(l1);
}

/*
    Desenha um triângulo preenchido e animado.
*/
void Example_Triangle()
{
    // Desenhamos um simples triângulo.
	Color e;
	e.r = 255;
	e.g = 0;
	e.b = 0;
	e.a = 255;

	Color f;
	f.r = 0;
	f.g = 255;
	f.b = 0;
	f.a = 255;

	Color c;
	c.r = 0;
	c.g = 0;
	c.b = 255;
	c.a = 255;
	
	Triangle t;
	t.a0.c = c;
	t.a1.c = f;
	t.a2.c = e;
	t.a0.p.x = IMAGE_WIDTH / 2;
	t.a0.p.y = 10;
	t.a1.p.x = 10;
	t.a1.p.y = IMAGE_HEIGHT - 10;
	t.a2.p.x = IMAGE_WIDTH - 10;
	t.a2.p.y = IMAGE_HEIGHT - 10;

	DrawTriangle(t);
}





int min(int i, int j)
{
    return i < j ? i : j;
}

int max(int i, int j)
{
    return i < j ? j : i;
}


void clear(int x0, int y0, int x1, int y1)
{
    int xi = min(x0, x1), xf = max(x0, x1), yi = min(y0, y1), yf = max(y0, y1);
    ColoredPoint cp;
    cp.c.r = cp.c.g = cp.c.b = 0;
    for (cp.p.x = xi; cp.p.x <= xf; cp.p.x++)
    {
        for (cp.p.y = yi; cp.p.y <= yf; cp.p.y++)
        {
            PutPixel(cp);
        }
    }
}

/*
    Desenha um triângulo preenchido e animado.
*/
void Example_FilledTriangle(int delta)
{
    float d1 = (PI/(float)25)*((float)delta), d2 = (PI/(float)45)*((float)delta), d3 = (PI/(float)11)*((float)delta) + 2;
    // Desenhamos um simples triângulo.

    clear(0, 0, IMAGE_WIDTH - 1, IMAGE_HEIGHT - 1);

	Color e;
	e.r = 255;
	e.g = 0;
	e.b = 0;
	e.a = 255;

	Color f;
	f.r = 0;
	f.g = 255;
	f.b = 0;
	f.a = 255;

	Color c;
	c.r = 0;
	c.g = 0;
	c.b = 255;
	c.a = 255;
	
	Triangle t;
	t.a0.c = c;
	t.a1.c = f;
	t.a2.c = e;
	t.a0.p.x = (IMAGE_WIDTH / 4) + (int)(sin(d1) * (float)(4*IMAGE_HEIGHT / 16));
	t.a0.p.y = 150 + (int)(cos(d1) * (float)(4*IMAGE_HEIGHT / 16));
	t.a1.p.x = 120 + (int)(sin(d2) * (float)(4*IMAGE_HEIGHT / 16));
	t.a1.p.y = IMAGE_HEIGHT - 200 + (int)(cos(d2) * (float)(4*IMAGE_HEIGHT / 16));
	t.a2.p.x = IMAGE_WIDTH - 150 + (int)(sin(d3) * (float)(4*IMAGE_HEIGHT / 16));
	t.a2.p.y = IMAGE_HEIGHT / 2 - 10 + (int)(sin(d3) * (float)(4*IMAGE_HEIGHT / 14));

	DrawAndFillTriangle(t);
}

#endif // _MYGL_H_

