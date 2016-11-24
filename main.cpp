/// Laboratorium: Grafika Komputerowa
/// Prowadzący: Dr inż. Marek Woda
/// Cw 2
/// Zbigniew Czarnecki 209909

#include <GL/glut.h>

/*************************************************************************************/

void drawRect(float x, float y, float bok);
void dywanSierpinskiegoKsztalt(int n, float x, float y, float bok);
void dywanSierpinskiego(int n, float x, float y, float bok);
float randColor();
void setRandColor();
float mixPosition(float position);
void topLeft(float x, float y, float przesuniecie);
void topRight(float x, float y, float przesuniecie);
void bottomLeft(float x, float y, float przesuniecie);
void bottomRight(float x, float y, float przesuniecie);

float randColor()
{
    float color = rand() % 100 / 100.0f;
    return color;
}

void setRandColor()
{
    float red = randColor();
    float green = randColor();
    float blue = randColor();
    glColor3f(red, green, blue);
}

float mixPosition(float position)
{
    float shift = rand() % 10 / 5 - 1;
    float result = position + shift;
    return result;
}

void topLeft(float x, float y, float przesuniecie)
{
    float pozycjaX = x - przesuniecie;
    float pozycjaY = y - przesuniecie;
    pozycjaX = mixPosition(pozycjaX);
    pozycjaY = mixPosition(pozycjaY);
    glVertex2f(pozycjaX, pozycjaY);
}

void topRight(float x, float y, float przesuniecie)
{
    float pozycjaX = x + przesuniecie;
    float pozycjaY = y - przesuniecie;
    pozycjaX = mixPosition(pozycjaX);
    pozycjaY = mixPosition(pozycjaY);
    glVertex2f(pozycjaX, pozycjaY);
}

void bottomLeft(float x, float y, float przesuniecie)
{
    float pozycjaX = x - przesuniecie;
    float pozycjaY = y + przesuniecie;
    pozycjaX = mixPosition(pozycjaX);
    pozycjaY = mixPosition(pozycjaY);
    glVertex2f(pozycjaX, pozycjaY);
}

void bottomRight(float x, float y, float przesuniecie)
{
    float pozycjaX = x + przesuniecie;
    float pozycjaY = y + przesuniecie;
    pozycjaX = mixPosition(pozycjaX);
    pozycjaY = mixPosition(pozycjaY);
    glVertex2f(pozycjaX, pozycjaY);
}

void drawRect(float x, float y, float bok)
{
    float przesuniecie = bok / 2;
    glBegin(GL_POLYGON);
    setRandColor();
    topLeft(x, y, przesuniecie);
    setRandColor();
    topRight(x, y, przesuniecie);
    setRandColor();
    bottomRight(x, y, przesuniecie);
    setRandColor();
    bottomLeft(x, y, przesuniecie);
    glEnd();
}

void dywanSierpinskiegoKsztalt(int n, float x, float y, float bok)
{
    float przesuniecie = bok / 3;
    n--;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i != 1 || j != 1) {
                float pozycjaX = x - przesuniecie + i * przesuniecie;
                float pozycjaY = y - przesuniecie + j * przesuniecie;
                dywanSierpinskiego(n, pozycjaX, pozycjaY, przesuniecie);
            }
        }
    }
}

void dywanSierpinskiego(int n, float x, float y, float bok)
{
    if (n == 0) {
        drawRect(x, y, bok);
    } else {
        dywanSierpinskiegoKsztalt(n, x, y, bok);
    }
}

/*************************************************************************************/
void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszcz¹cym
    glColor3f(0.0f, 1.0f, 0.0f);
    // Ustawienie aktualnego koloru rysowania na zielony

    int level = 3;
    float x = 0.0f;
    float y = 0.0f;

    float bok = 180.0f;

    glClear(GL_COLOR_BUFFER_BIT);
    dywanSierpinskiego(level, x, y, bok);
    glFlush();

}
/*************************************************************************************/
// Funkcja ustalająca stan renderowania

void MyInit(void)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    // Kolor okna wnętrza okna - ustawiono na szary
}
/*************************************************************************************/
// Funkcja służąca do kontroli zachowania proporcji rysowanych obiektów
// niezależnie od rozmiarów okna graficznego


void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szerokość i wysokość okna) są
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna
{
    GLfloat AspectRatio;
    // Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna

    if(vertical==0)
// Zabezpieczenie pzred dzieleniem przez 0
        vertical = 1;

    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkościokna okna urządzenia (Viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)

    glMatrixMode(GL_PROJECTION);
// Określenie układu współrzędnych obserwatora
    glLoadIdentity();
    // Określenie przestrzeni ograniczającej
    AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
// Wyznaczenie współczynnika proporcji okna
// Gdy okno na ekranie nie jest kwadratem wymagane jest
// określenie okna obserwatora.
// Pozwala to zachować właściwe proporcje rysowanego obiektu
// Do określenia okna obserwatora służy funkcja glOrtho(...)

    if(horizontal <= vertical)
        glOrtho(-100.0,100.0,-100.0/AspectRatio,100.0/AspectRatio,1.0,-1.0);
    else
        glOrtho(-100.0*AspectRatio,100.0*AspectRatio,-100.0,100.0,1.0,-1.0);
    glMatrixMode(GL_MODELVIEW);
// Określenie układu współrzędnych
    glLoadIdentity();
}
/*************************************************************************************/
// Główny punkt wejścia programu. Program działa w trybie konsoli

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    // Ustawienie trybu wyświetlania
    // GLUT_SINGLE - pojedynczy bufor wyświetlania
    // GLUT_RGBA - model kolorów RGB

    glutCreateWindow("Drugi program w OpenGL");
    // Utworzenie okna i określenie treści napisu w nagłówku okna

    glutDisplayFunc(RenderScene);
    // Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
    // Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
    // trzeba będzie przerysować okno


    glutReshapeFunc(ChangeSize);
    // Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną za
    // zmiany rozmiaru okna

    MyInit();
    // Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie
    // inicjalizacje konieczneprzed przystąpieniem do renderowania

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

    return 0;

}
/*************************************************************************************/