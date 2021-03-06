#include<iostream>
#include<string>


using namespace std;

int br[100], brc[100], qr[100], a[100] = { 0 }, bits1 = 0, bits2 = 0;
void addbr(int);
void addbrc(int);
void display(int[], int, int, string, int);


int main()
{
    int no1, no2, temp1, temp2, b[100], i = 0, bi = 0, j, c[100], lena, lenb, ai;
    string s;
    cout << "-----ALGORITMO DE BOOTH-----"<<endl;
    cout << "Ingresa Q:";
    cin >> no1;
    cout << "Ingresa A:";
    cin >> no2;
    temp1 = no1;
    temp2 = no2;
    while (no1)
    {
        no1 = no1 / 2;
        bits1++;
    }
    while (no2)
    {
        no2 = no2 / 2;
        bits2++;
    }
    if (bits1 > bits2)
    {
        no1 = temp1;
        no2 = temp2;
    }
    else
    {
        no1 = temp2;
        no2 = temp1;
        swap(bits1, bits2);
    }
    if (no1 < 0)
    {
        no1 = -no1;
        bi = 0;
        while (no1)
        {
            if (no1 % 2 == 0)
                b[bi] = 1;
            else
                b[bi] = 0;
            no1 = no1 / 2;
            bi++;
        }
        for (j = 0; j < bi; j++)
        {
            if (b[j] == 1)
                b[j] = 0;
            else
            {
                b[j] = 1;
                break;
            }
        }
        b[bi] = 1;
        bi++;
    }
    else
    {
        bi = 0;
        while (no1)
        {
            b[bi] = no1 % 2;
            no1 = no1 / 2;
            bi++;
        }
        b[bi] = 0;
        bi++;
    }
    if (no2 < 0)
    {
        no2 = -no2;
        ai = 0;
        while (no2)
        {
            if (no2 % 2 == 0)
                c[ai] = 1;
            else
                c[ai] = 0;
            no2 = no2 / 2;
            ai++;
        }
        if (bits1 != bits2)
        {
            while (bits1 != ai)
            {
                c[ai] = 1;
                ai++;
            }
        }
        for (j = 0; j < ai; j++)
        {
            if (c[j] == 1)
                c[j] = 0;
            else
            {
                c[j] = 1;
                break;
            }
        }
        c[ai] = 1;
        ai++;
    }
    else
    {
        ai = 0;
        while (no2)
        {
            c[ai] = no2 % 2;
            no2 = no2 / 2;
            ai++;
        }
        if (bits1 != bits2)
        {
            while (bits1 != ai)
            {
                c[ai] = 0;
                ai++;
            }
        }
        c[ai] = 0;
        ai++;
    }
    lena = 0; lenb = 0;
    for (j = bi - 1; j >= 0; j--)
    {
        br[lena] = b[j];
        if (br[lena] == 1)
            brc[lena] = 0;
        else
            brc[lena] = 1;
        lena++;
    }
    for (j = bi - 1; j >= 0; j--)
    {
        if (brc[j] == 1)
            brc[j] = 0;
        else
        {
            brc[j] = 1;
            break;
        }
    }
    for (j = ai - 1; j >= 0; j--)
    {
        qr[lenb] = c[j];
        lenb++;
    }
    int x = 0;
    for (j = bi; j < ai + bi; j++)
    {
        a[j] = qr[x];
        x++;
    }
    cout << "\nBr=";
    for (j = 0; j < bi; j++)
    {
        cout << br[j];
    }
    cout << "\nBrc=";
    for (j = 0; j < bi; j++)
    {
        cout << brc[j];
    }
    cout << "\nQr=";
    for (j = 0; j < ai; j++)
    {
        cout << qr[j];
    }
    cout << "\nqn   qn+1   A       Q       n    comment\n";
    bits2 = bi;
    while (bits2 != 0)
    {
        if (a[ai + bi - 1] == 0 && a[ai + bi] == 1)
        {
            addbr(bi);
            s = "Add_Br";
            display(a, ai, bi, s, bits2);
            for (i = ai + bi; i > 0; i--)
            {
                a[i] = a[i - 1];
            }
        }
        else
            if (a[ai + bi - 1] == 1 && a[ai + bi] == 0)
            {
                addbrc(bi);
                s = "Add_Brc";
                display(a, ai, bi, s, bits2);
                for (i = ai + bi; i > 0; i--)
                {
                    a[i] = a[i - 1];
                }
            }
            else
            {
                for (i = ai + bi; i > 0; i--)
                {
                    a[i] = a[i - 1];
                }
            }
        s = "ashr";
        display(a, ai, bi, s, bits2);
        bits2--;
    }
    cout << "\nRES=";
    int ans = 0, d = 0, f[100];
    if (a[0] == 0)
    {
        for (i = ai + bi - 1; i >= 0; i--)
        {
            ans = ans + a[i] * pow(2, d);
            d++;
        }
        cout << ans;
    }
    else
    {
        for (i = 0; i < ai + bi; i++)
        {
            if (a[i] == 0)
                f[i] = 1;
            else
                f[i] = 0;
        }
        for (i = ai + bi - 1; i >= 0; i--)
        {
            if (f[i] == 1)
                f[i] = 0;
            else
            {
                f[i] = 1;
                break;
            }
        }
        for (i = ai + bi - 1; i >= 0; i--)
        {
            ans = ans + f[i] * pow(2, d);
            d++;
        }
        ans = -ans;
        cout << ans;
    }

}
void addbr(int xi)
{
    int ax = 0;
    for (int i = xi - 1; i >= 0; i--)
    {
        a[i] = a[i] + br[i] + ax;
        if (a[i] == 2)
        {
            ax = 1;
            a[i] = 0;
        }
        else
            if (a[i] == 3)
            {
                ax = 1;
                a[i] = 1;
            }
            else
                ax = 0;
    }
}
void addbrc(int xi)
{
    int ax = 0;
    for (int i = xi - 1; i >= 0; i--)
    {
        a[i] = a[i] + brc[i] + ax;
        if (a[i] == 2)
        {
            ax = 1;
            a[i] = 0;
        }
        else
            if (a[i] == 3)
            {
                ax = 1;
                a[i] = 1;
            }
            else
                ax = 0;
    }
}
void display(int a[], int m, int n, string sh, int bit)
{
    cout << a[m + n - 1] << "    " << a[m + n] << "    ";
    for (int axi = 0; axi < m + n; axi++)
    {
        cout << a[axi];
        if (axi == m - 1)
            cout << "     ";
        if (axi == m + n - 1)
            cout << "     ";
    }
    cout << "   " << bit << "   " << sh << endl;
}
