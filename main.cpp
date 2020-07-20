#include <iostream>
#include <graphics.h>
#include <fstream>
using namespace std;


struct nod
{
    int nr,poz;
    nod *st, *dr;
}*r;

ifstream f("date.in");

int t,k,x0,y0,v,p,x2,y2,coord[100][4],inainte,iesire,noduri[100],copnoduri[100],n;
int ad[10]= {0,-90,50,90,120,140,160,180,200},var,alg,vardelay,cn,ramase[100],l,var2;

//inserare nod
void inserare(nod *&r, int k, int e)
{
    if(r)
    {
        if(r->nr>k)
        {

            x0=coord[r->poz][2]-200;
            y0=coord[r->poz][3]+80;
            p++;
            v=1;
            inainte=r->poz;
            inserare(r->st,k,e);
        }
        else
        {
            x0=coord[r->poz][2]+200;
            y0=coord[r->poz][3]+80;
            p++;
            v=2;
            inainte=r->poz;
            inserare(r->dr,k,e);
        }
    }
    else
    {
        if(p>6)
        {
            l++;
            ramase[e]=1;
            r=new nod;
            r->nr=k;
            r->poz=e;
            r->dr=0;
            r->st=0;

            int j;
            j=ad[p];
            if(v==1)
                x2=x0+j;
            else
                x2=x0-j;
            y2=y0;

            coord[e][1]=k;
            coord[e][2]=x2;
            coord[e][3]=y2;
        }
        else
        {
            r=new nod;
            r->nr=k;
            r->poz=e;
            r->dr=0;
            r->st=0;

            t++;
            char *s;
            int j;
            s=new char;
            itoa(k,s,10);
            j=ad[p];

            if(v==1)
            {
                outtextxy(x0+j,y0,s);
                circle(x0+j+9,y0+11,20);
                x2=x0+j;
            }
            else
            {
                outtextxy(x0-j,y0,s);
                circle(x0-j+9,y0+11,20);
                x2=x0-j;
            }
            y2=y0;

            coord[e][1]=k;
            coord[e][2]=x2;
            coord[e][3]=y2;

            if(t!=1)
            {
                setcolor(15);
                line(coord[inainte][2]+8,coord[inainte][3]+30,x2,y2-8);
            }
        }
    }
}
//creare
void creare()
{
    //creare primul nod
    if(n!=0)
    {
        int j=1;
        while(copnoduri[j]<0)
            j++;
        r=new nod;
        r->nr=copnoduri[j];
        r->poz=j;
        r->st=0;
        r->dr=0;
        coord[j][1]=r->nr;
        coord[j][2]=725;
        coord[j][3]=10;
        char *s;
        s=new char;
        itoa(r->nr,s,10);
        outtextxy(725,10,s);
        circle(725+9,10+11,20);
        if(vardelay==1)
            delay(500);

        t=1;
        l=0;

        //creare arbore
        for(int i=j+1; i<=n; i++)
        {
            if(copnoduri[i]>=0)
            {
                p=0;
                v=0;
                inserare(r,copnoduri[i],i);
                setcolor(14);
                if(vardelay==1)
                    delay(500);
            }
        }
    }

    //afisare ramase
    var2=0;
    outtextxy(10,530,"NODURI CARE NU SE INCADREAZA PE ECRAN: ");
    if(l)
    {
       for(int i=1;i<=n;i++)
       {
           if(ramase[i]==1 && copnoduri[i]!=-1)
           {
                char *s;
                s=new char;
                itoa(copnoduri[i],s,10);
                outtextxy(480+var2,530,s);
                var2=var2+40;
           }
       }
    }
    outtextxy(10,560,"CE DORITI SA SE INTAMPLE?");
    outtextxy(10,580,"0 - IESIRE");
    outtextxy(10,600,"1 - PARCURGERE");
    outtextxy(10,620,"2 - CAUTARE");
    outtextxy(10,640,"3 - ADAUGARE");
    outtextxy(10,660,"4 - STERGERE");
    outtextxy(10,680,"5 - RESETARE");

    vardelay=2;
}

//parcurgere
void srd(nod *r)
{
    if(r)
    {
        srd(r->st);

        char *s;
        s=new char;
        itoa(r->nr,s,10);
        setcolor(14);
        outtextxy(10+var,720,s);
        var=var+40;

        if(ramase[r->poz]==0)
        {
            setcolor(9);
            outtextxy(coord[r->poz][2],coord[r->poz][3],s);
        }

        delay(600);

        srd(r->dr);
    }
}

//cautare
void cautare(nod *r,int k)
{
    if(r)
    {
        if(r->nr==k)
        {
            outtextxy(120,720,"-->> GASIT");

            if(ramase[r->poz]==0)
            {
                setcolor(9);
                char *s;
                s=new char;
                itoa(r->nr,s,10);
                outtextxy(coord[r->poz][2],coord[r->poz][3],s);
            }
        }
        else
        {
            if(r->nr>k) cautare(r->st,k);
            else cautare(r->dr,k);
        }
    }
    else outtextxy(120,720,"-->> NEGASIT");
}

//stergere
nod *g;
void cmmnd( nod *&r, nod *&g)
{
    nod *man;
    if(g->dr!=0) cmmnd(r,g->dr);
    else
    {
        r->nr=g->nr;
        man=g->st;
        delete g;
        g=man;
    }
}

void sterge (nod *&r, int k)
{
    nod *g;
    if(r)
    {
        if(r->nr==k)
        {
            if(r->st==0 && r->dr==0)
            {
                delete r;
                r=0;
            }
            else
            {
                if(r->dr==0)
                {
                    g=r->st;
                    delete r;
                    r=g;
                }
                else
                {
                    if(r->st==0)
                    {
                        g=r->dr;
                        delete r;
                        r=g;
                    }
                    else cmmnd(r,r->st);
                }
            }
        }
    }
    else
    {
        if(r->nr<k) sterge(r->st,k);
        else sterge (r->dr,k);
    }
}

//sdr
void sdr(nod *&r)
{
    if(r)
    {
        sdr(r->st);
        sdr(r->dr);
    }
    delete r;
}

//main
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    initwindow(1500,770, "ARBORE BINAR DE CAUTARE");

    setcolor(14);
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);

    outtextxy(10,10,"APASATI ORICE TASTA PENTRU A AFISA ARBORELE BINAR!");

    getch();

    cleardevice();

    //citire noduri
    n=0;
    while(f>>k)
    {
        n++;
        noduri[n]=k;
        copnoduri[n]=k;
    }

    cn=n;

    //menu
    vardelay=1;
    alg=1;
    while(alg)
    {

        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        setlinestyle(SOLID_LINE,0,2);

        creare();
        setbkcolor(0);
        cout<<"INTRODUCETI VALOAREA: ";
        cin>>alg;

        while(alg!=0 && alg!=1 && alg!=2 && alg!=3 && alg!=4 && alg!=5)
        {
            outtextxy(10,700,"ALEGERE INCORECTA!!");
            cout<<"INTRODUCETI VALOAREA: ";
            cin>>alg;
        }

        if(alg==1) //parcurgere
        {
            outtextxy(10,700,"PARCURGEREA ESTE:        ");
            srd(r);
        }
        if(alg==2) //cautare
        {
            outtextxy(10,700,"INTRODUCETI VALOAREA CE TREBUIE CAUTATA!");
            cout<<"VALOARE CE TREBUIE CAUTATA: ";
            int caut;
            cin>>caut;
            cautare(r,caut);
        }
        if(alg==3) //adaugare
        {
            outtextxy(10,700,"INTRODUCETI VALOAREA CE TREBUIE ADAUGATA!");
            cout<<"VALOARE CE TREBUIE ADAUGATA: ";
            int adaug;
            cin>>adaug;
            n++;
            copnoduri[n]=adaug;
            p=0;
            v=0;
            inserare(r,adaug,n);
            if(ramase[n]==1)
            {
                char *s;
                s=new char;
                itoa(copnoduri[n],s,10);
                outtextxy(480+var2,530,s);
                var2=var2+40;
            }
        }
        if(alg==4) //stergere
        {
            outtextxy(10,700,"INTRODUCETI VALOAREA CE TREBUIE STEARSA!");
            cout<<"VALOARE CE TREBUIE STEARSA: ";
            int sterg;
            cin>>sterg;
            int i=1,pp=1;
            while(i<=n && pp)
            {
                if(copnoduri[i]==sterg)
                {
                    copnoduri[i]=-1;
                    sterge(r,sterg);
                    cleardevice();
                    vardelay++;
                    creare();
                    pp=0;
                }
                i++;
            }
            if(pp) outtextxy(10,700,"NU EXISTA VALOAREA IN ARBORE!               ");
        }
        if(alg==5) //resetare
        {
            cleardevice();
            for(int i=1;i<=n;i++)
                copnoduri[i]=noduri[i];
            n=cn;
            creare();
        }

        //reinitializare
        setcolor(14);
        if(alg!=0)
        {
            outtextxy(30,740,"-> APASATI ORICE TASTA APOI ENTER PT. A CONTINUA! <-");
            char c;
            cin>>c;
        }
        sdr(r);
        for(int i=1;i<=n;i++)
        {
            coord[i][1]=0;
            coord[i][2]=0;
            coord[i][3]=0;
            ramase[i]=0;
        }

        var=0;
        vardelay++;

        cleardevice();
    }
    closegraph();
    return 0;
}
