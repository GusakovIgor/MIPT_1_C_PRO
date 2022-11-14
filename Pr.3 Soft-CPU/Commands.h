/*** System ***/

DEF_CMD (HLT,   0, 0,
                    {
                    processor->pc = processor->code_size;
                    })

DEF_CMD (START, 1, 0,
                    {
                    processor->pc = *(int*)(processor->code + processor->pc + 1);
                    })

DEF_CMD (IN,    2, 0,
                    {
                    int number = 0;

                    scanf ("%d", &number);

                    StackPush (processor->stack, number);

                    processor->pc++;
                    })

DEF_CMD (NOUT,  3, 0,
                    {
                    double number = StackPop (processor->stack);

                    if (number > 1e9)
                    {
                        printf ("%.lg", number);
                    }
                    else
                    {
                        int precision = ((number - (int) number) == 0) ? 0 : 3;

                        printf ("%.*lf", precision, number);
                    }


                    processor->pc++;
                    })

DEF_CMD (SOUT,  4, 0,
                    {
                    double adress = StackPop (processor->stack);

                    printf ("%s", (char*) RAM + (int) adress);

                    processor->pc++;
                    })

DEF_CMD (DB,    5, 1,
                    {
                    processor->pc++;

                    int length = strlen (processor->code + processor->pc);


                    if (free_data + length < DATA_SIZE)
                    {
                        strcpy ((char*) RAM + RAM_SIZE + free_data, processor->code + processor->pc);
                    }

                    StackPush (processor->stack, RAM_SIZE + free_data);

                    free_data += length + 1;

                    processor->pc += length + 1;
                    })



/*** Stack **/

DEF_CMD (PUSH, 10, 2,
                    {
                    ++processor->pc;

                    int mode = processor->code[processor->pc++];

                    StackPush (processor->stack, ArgGetter(processor, mode, RAM));
                    })

DEF_CMD (POP,  11, 2,
                    {
                    double temp = StackPop (processor->stack);
                    ++processor->pc;

                    int mode = processor->code[processor->pc++];

                    double arg = 0;

                    if (mode & 1)
                    {
                        arg += processor->registers[processor->code[processor->pc++]];
                    }
                    if ((mode & 2)/2)
                    {
                        arg += *(double*)(processor->code + processor->pc);
                        processor->pc += sizeof(double);
                    }
                    if ((mode & 4)/4)
                    {
                        *(RAM + (int) arg) = temp;
                    }
                    else
                    {
                        processor->registers[processor->code[processor->pc - 1]] = temp;
                    }

                    })



/*** Arithmetic ***/

DEF_CMD (ADD,  15, 0,
                    {
                    StackPush (processor->stack, StackPop(processor->stack) + StackPop(processor->stack));
                    processor->pc++;
                    })

DEF_CMD (SUB,  16, 0,
                    {
                    double temp = StackPop (processor->stack);
                    StackPush (processor->stack, StackPop(processor->stack) - temp);
                    processor->pc++;
                    })

DEF_CMD (MULT, 17, 0,
                    {
                    StackPush (processor->stack, StackPop(processor->stack) * StackPop(processor->stack));
                    processor->pc++;
                    })

DEF_CMD (DIV, 18, 0,
                    {
                    double temp = StackPop (processor->stack);
                    if (temp != 0)
                        StackPush (processor->stack, StackPop(processor->stack) / temp);
                    else
                        {
                            printf ("Trying to segment by zero");
                            assert (!"OK");
                        }
                    processor->pc++;
                    })

DEF_CMD (POW,  19, 0,
                    {
                    int temp = StackPop(processor->stack);
                    StackPush (processor->stack, pow(StackPop(processor->stack), temp));
                    processor->pc++;
                    })

DEF_CMD (SQRT, 20, 0,
                    {
                    StackPush (processor->stack, sqrt(StackPop(processor->stack)));
                    processor->pc++;
                    })

DEF_CMD (SIN, 21, 0,
                    {
                    StackPush (processor->stack, sin(StackPop(processor->stack)));
                    processor->pc++;
                    })

DEF_CMD (COS, 22, 0,
                    {
                    StackPush (processor->stack, cos(StackPop(processor->stack)));
                    processor->pc++;
                    })

DEF_CMD (LROUND, 23, 0,
                    {
                       double temp = StackPop(processor->stack);
                       StackPush (processor->stack, lround(temp));
                       processor->pc += sizeof (char);
                    })



/*** Jumps ***/

DEF_CMD (JMP, 30, 1,
                    {
                    processor->pc = *(int*)(processor->code + processor->pc + 1);
                    })

DEF_CMD (JA,  31, 1,
                    {
                    double temp1 = StackPop(processor->stack);
                    double temp2 = StackPop(processor->stack);
                    if (temp2 > temp1)
                        {
                            processor->pc = *(int*)(processor->code + processor->pc + 1);
                        }
                    else
                        {
                            processor->pc += sizeof(char) + sizeof(int);
                        }
                    })

DEF_CMD (JAE, 32, 1,
                    {
                    double temp1 = StackPop(processor->stack);
                    double temp2 = StackPop(processor->stack);
                    if (temp2 >= temp1)
                        {
                            processor->pc = *(int*)(processor->code + processor->pc + 1);
                        }
                    else
                        {
                            processor->pc += sizeof(char) + sizeof(int);
                        }
                    })

DEF_CMD (JB,  33, 1,
                    {
                    double temp1 = StackPop(processor->stack);
                    double temp2 = StackPop(processor->stack);
                    if (temp2 < temp1)
                        {
                            processor->pc = *(int*)(processor->code + processor->pc + 1);
                        }
                    else
                        {
                            processor->pc += sizeof(char) + sizeof(int);
                        }
                    })

DEF_CMD (JBE, 34, 1,
                    {
                    double temp1 = StackPop(processor->stack);
                    double temp2 = StackPop(processor->stack);
                    if (temp2 <= temp1)
                        {
                            processor->pc = *(int*)(processor->code + processor->pc + 1);
                        }
                    else
                        {
                            processor->pc += sizeof(char) + sizeof(int);
                        }
                    })

DEF_CMD (JE,  35, 1,
                    {
                    double temp1 = StackPop(processor->stack);
                    double temp2 = StackPop(processor->stack);
                    if (temp2 == temp1)
                        {
                            processor->pc = *(int*)(processor->code + processor->pc + 1);
                        }
                    else
                        {
                            processor->pc += sizeof(char) + sizeof(int);
                        }
                    })

DEF_CMD (JNE, 36, 1,
                    {
                    double temp1 = StackPop(processor->stack);
                    double temp2 = StackPop(processor->stack);
                    if (temp2 != temp1)
                        {
                            processor->pc = *(int*)(processor->code + processor->pc + 1);
                        }
                    else
                        {
                            processor->pc += sizeof(char) + sizeof(int);
                        }
                    })

DEF_CMD (JT,  37, 1,
                    {

                    })



/*** Functions ***/

DEF_CMD (CALL, 40, 1,
                    {
                    StackPush (processor->calls, processor->pc + sizeof(char) + sizeof(int));
                    processor->pc = *(int*)(processor->code + processor->pc + 1);
                    })

DEF_CMD (RET,  41, 0,
                    {
                    processor->pc = StackPop(processor->calls);
                    })



/*** Special ***/


// DEF_CMD (DRAW, 27, 3,
//                     {
//                     printf ("VSE SLOGHNO\n");
//                     const int X_size = RAM[0];
//                     const int Y_size = RAM[1];

//                     processor->pc += sizeof(char);
//                     int R = *(int*)(processor->code + processor->pc);

//                     processor->pc += sizeof(int);
//                     int G = *(int*)(processor->code + processor->pc);

//                     processor->pc += sizeof(int);
//                     int B = *(int*)(processor->code + processor->pc);

//                     processor->pc += sizeof(int);

//                     RGBQUAD* BUFF = txVideoMemory();
//                     assert (BUFF);
//                     txLock();
//                     for (int i = 0; i < X_size*Y_size; i++)
//                         if (VRAM[i])
//                         {
//                             (*(BUFF + i)).rgbRed   = R;
//                             (*(BUFF + i)).rgbGreen = G;
//                             (*(BUFF + i)).rgbBlue  = B;
//                         }
//                     txUnlock();
//                     txRedrawWindow();

//                     })

// DEF_CMD (CREATEWINDOW, 28, 3,
//                     {
//                     const int X_size = RAM[0];
//                     const int Y_size = RAM[1];

//                     //txCreateWindow (X_size, Y_size);

//                     Application* App = (Application*) calloc (1, sizeof(Application));

//                     SDL_Init (App);

//                     processor->pc += sizeof(char);
//                     int R = *(int*)(processor->code + processor->pc);

//                     processor->pc += sizeof(int);
//                     int G = *(int*)(processor->code + processor->pc);

//                     processor->pc += sizeof(int);
//                     int B = *(int*)(processor->code + processor->pc);

//                     txSetFillColor (RGB(R, G, B));
//                     txRectangle (0, Y_size, X_size, 0);

//                     processor->pc += sizeof (int);
//                     })