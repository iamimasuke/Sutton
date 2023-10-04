using System;
using System.Collections.Generic;

//入力された数字までのすべての素数を求めるためのクラス
class Calc
{
    private int num;
    public Calc(int Num){
        num = Num;
    }

    public List<int> calc()
    {
       
        //素数を格納する配列
        List<int> primeList = new List<int>();

        //jが素数か判定　jは2からnumまで
        for (int j = 2; j <= num; j++){
            //判定する数字(j)の平方根
            int sq = (int)Math.Sqrt(j);
            for (int i = 1; i <= sq; i++){
                int div = j % i;
                if(i != 1 && div == 0)break;
                if (i == sq){
                    primeList.Add(j);
                    //breakはなくてもいい、なんとなく
                    break;
                }
            }
        }
        return primeList;
    }

    public List<int> efficientCalc()
    {

        //素数を格納する配列
        List<int> primeList = new List<int>();
        //foreach使うために最初から2だけは入れておく。
        primeList.Add(2);
        //jが素数か判定　jは2からnumまで
        for (int j = 3; j <= num; j++)
        {
            //判定する数字(j)の平方根
            int sq = (int)Math.Sqrt(j);
            foreach(int i in primeList){
                int div = j % i;
                if (div == 0) break;
                if (i>sq){
                    primeList.Add(j);
                    break;
                }
            }
        }
        return primeList;
    }
}

class Program
{
    static void Main(string[] args)
    {
        //文字列として数字を入力
        string userInput = Console.ReadLine();
        //文字列から整数型に変換
        int.TryParse(userInput, out int input);
        Calc collectPrimes = new Calc(input);

        //List<int> pNums = collectPrimes.efficientCalc();
        List<int> pNums = collectPrimes.calc();
        Console.WriteLine(input + "までの素数は");
        for (int i = 0; i < pNums.Count; i++){
            if(i != (pNums.Count-1))Console.Write(pNums[i]+",");
            else Console.Write(pNums[i]+"\n");
        }
        Console.WriteLine("です");
        Console.Write("合計の素数の数は" + pNums.Count + "個です。");

        
    }
}
