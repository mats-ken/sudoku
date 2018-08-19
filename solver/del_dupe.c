/* リストを元にチェック */
void        del_dupe2(TABLE*t, int*num)
{
  int         i, j;
  int         flag[9];

  for(i = 0; i < 9; i++)
    flag[i] = 0;

  for(i = 0; i < 9; i++)
    if(t[num[i]].fixed)
      flag[t[num[i]].fixed - 1] = 1;

  for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++)
      if(flag[j] && !t[num[i]].fixed)
        t[num[i]].flag[j] = 0;
}

/* リスト作成してdel_dupe2()を呼ぶ */
void        del_dupe(TABLE*t)
{
  int         i, j, k, n;
  int         flag[9];
  int         num[9];

  do{

    /* holizontal */
    for(i = 0; i < 9; i++){
      for(j = 0; j < 9; j++)
        num[j] = i * 9 + j;
      del_dupe2(t, num);
    }

    /* vertical */
    for(i = 0; i < 9; i++){
      for(j = 0; j < 9; j++)
        num[j] = i + j * 9;
      del_dupe2(t, num);
    }

    /* 3x3 box */
    for(i = 0; i < 9 * 9; i += 27){
      for(j = 0; j < 9; j += 3){
        n = 0;

        for(k = 0; k < 3; k++)
          num[n++] = i + j + k;
        for(k = 0; k < 3; k++)
          num[n++] = i + j + k + 9;
        for(k = 0; k < 3; k++)
          num[n++] = i + j + k + 18;

        del_dupe2(t, num);
      }
    }
  }while(chk_fixed(t));
}
