/**
  ******************************************************************************
  * Donald Wight
  *Extra Credit
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
//

//***********************************************************
//#define for all of the boundries. Makes it easy to adjust and it will adjust it automatically in the code
#define         Y_MIN          0
#define         Y_MAX          320
//boundries for where it will respond to a touch
#define         X1_MIN         2
#define         X1_MAX         64

#define         X2_MIN         89
#define         X2_MAX         153

#define         X3_MIN         176
#define         X3_MAX         238
//boundries for the box, with a black outline
#define         blk_height     60
#define         blk_offset     30 
#define         clr_height     50
#define         clr_offset     25


extern uint32_t CurrentFrameBuffer;

void LCD_ClearSection(uint16_t, uint16_t);
int TimingDelay;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  // default positions for box 1 2 and 3 (the sliders)
  int x1_box = Y_MAX/2;
  int x2_box = Y_MAX/2;
  int x3_box = Y_MAX/2;
  // where we have the lines in the middle of the boundries for each 
  int line_1 = (X1_MIN+X1_MAX)/2;
  int line_2 = (X2_MIN+X2_MAX)/2;
  int line_3 = (X3_MIN+X3_MAX)/2;
  int draw = 0;
  static TP_STATE* TP_State; 

  /* LCD initialization */
  LCD_Init();
  
  /* LCD Layer initialization */
  LCD_LayerInit();
    
  /* Enable the LTDC */
  LTDC_Cmd(ENABLE);
  
  /* Set LCD foreground layer */
  LCD_SetLayer(LCD_FOREGROUND_LAYER);
    
  while (1)
  {
 
      TP_State = IOE_TP_GetState();
      // if a touch is detected we enter
      if((TP_State->TouchDetected) && ((TP_State->Y < Y_MAX) && (TP_State->Y >= Y_MIN)))
      {
          // if it is th boundries for the first box
          if((TP_State->X >= X1_MIN) && (TP_State->X < X1_MAX))
          {   
              x1_box = TP_State->Y;
              draw=0;
          }
          // else if it is in the boundries for the 2nd box
          else if ((TP_State->TouchDetected) && (TP_State->X >= X2_MIN) && (TP_State->X < X2_MAX))
          {
                x2_box = TP_State->Y; 
                draw=0;
          } 
          // if it is in the boundries for the third box
          else if ((TP_State->TouchDetected) && (TP_State->X >= X3_MIN) && (TP_State->X < X3_MAX)) 
          {
                 x3_box = TP_State->Y;
                 draw=0;
          }
          
       }
      
      if (draw ==0 && !(TP_State->TouchDetected))
      {
        LCD_ClearSection(Y_MIN,Y_MAX);
        //draws three vertical lines
        LCD_SetTextColor(LCD_COLOR_BLACK);
        LCD_DrawLine(line_1, Y_MIN, Y_MAX, LCD_DIR_VERTICAL);
        LCD_DrawLine(line_2, Y_MIN, Y_MAX, LCD_DIR_VERTICAL);
        LCD_DrawLine(line_3, Y_MIN, Y_MAX, LCD_DIR_VERTICAL);
        //draws three boxes
        LCD_SetTextColor(LCD_COLOR_BLACK); 
        LCD_DrawFullRect(line_1-blk_offset,(x1_box-blk_offset) , blk_height, blk_height);
        LCD_SetTextColor(LCD_COLOR_RED); 
        LCD_DrawFullRect(line_1-clr_offset,(x1_box-clr_offset) , clr_height, clr_height);
        LCD_SetTextColor(LCD_COLOR_BLACK); 
        LCD_DrawFullRect(line_2-blk_offset,(x2_box-blk_offset) , blk_height, blk_height);
        LCD_SetTextColor(LCD_COLOR_GREEN); 
        LCD_DrawFullRect(line_2-clr_offset,(x2_box-clr_offset) , clr_height, clr_height);
        LCD_SetTextColor(LCD_COLOR_BLACK); 
        LCD_DrawFullRect(line_3-blk_offset,(x3_box-blk_offset) , blk_height, blk_height);
        LCD_SetTextColor(LCD_COLOR_BLUE); 
        LCD_DrawFullRect(line_3-clr_offset,(x3_box-clr_offset) , clr_height, clr_height);
       /* The only thing i didnt have time to do is to display a numerical value beneath the sliders 
        percent =variable_1(box_1/Y_MAX);
        percent =variable_2(box_2/Y_MAX);
        percent =variable_3(box_3/Y_MAX);
        */
        draw = 1;
      }
      
            
  }
}

// will omly clear section with the sliders so you dont use data
void LCD_ClearSection(uint16_t YStart, uint16_t YEnd)
{
    int x = 0;
    
    LCD_SetTextColor(LCD_COLOR_WHITE);
    for (x=0; x<=240; x++) 
      LCD_DrawLine(x, YStart, (YEnd - YStart), LCD_DIR_VERTICAL);
    
}
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

