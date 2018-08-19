/* リストを元にチェック */
int         chk_error2(TABLE*t, int*num)
{
  int         i, j;
  int         flag[9];

  for(i = 0; i < 9; i++)
    flag[i] = 0;

  for(i = 0; i < 9; i++){
    if(t[num[i]].fixed){
      if(flag[t[num[i]].fixed - 1])
        return -1;
      flag[t[num[i]].fixed - 1] = 1;
    }
  }

  return 0;
}

/* リスト作成してchk_error2()を呼ぶ */
int         chk_error(TABLE*t)
{
  int         i, j, k, n;
  int         flag[9];
  int         num[9];

  for(i = 0; i < 9 * 9; i++){
    n = 0;
    for(j = 0; j < 9; j++)
      n += t[i].flag[j];
    if(0 == n)
      return -1;
  }

  /* holizontal */
  for(i = 0; i < 9; i++){
    for(j = 0; j < 9; j++)
      num[j] = i * 9 + j;
    if(chk_error2(t, num) < 0)
      return -1;
  }

  /* vertical */
  for(i = 0; i < 9; i++){
    for(j = 0; j < 9; j++)
      num[j] = i + j * 9;
    if(chk_error2(t, num) < 0)
      return -1;
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

      if(chk_error2(t, num) < 0)
        return -1;
    }
  }

  return 0;
}
