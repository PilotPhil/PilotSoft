   M S B A M L   `   `   `  ����E  ASerialTest, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null1clr-namespace:SerialTest.ViewSerialTest.View  5   	       SerialTest.View.MainView   5   	   W SPresentationCore, Version=5.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=5.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=5.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089R NWindowsBase, Version=5.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=5.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   /localclr-namespace:SerialTest.View     5   	     � 
ResizeMode$  NoResize=�5   	    � Title$ Serial Test��5	   	   $	��460��6   $	��610��6*    � DataContext 5
   	   ��    Locator �� Source# [   �� Path$
 Main�.��5      �  � RowDefinitions 5   
   �� 5      $��3* �6   �� 5      $��2* �6    � ColumnDefinitions 5   
   �� 5      $
��Auto �6   �� 5      .+�5   
   ��  �� Orientation$ Vertical=�6   $��0��6,   $��0��69   $��2��6I   $	��Top=�6Z   .+�5      �� $��
Serial CFG��6   $	��165��6+   $	��210��67   $��5q�6D   .��5      �� $ Vertical=�6   .+�5      �� $ 
Horizontal=�6   $��5q�66   .+�5      �� $
��Port��6    $��60��6,   $
��Left=�67   $��Center=�6R   �� 5      $��80��6   ��5      �� * SerialNotifiableModel.PortList+ �� SelectedItem 5      �� *SerialNotifiableModel.Port+5      �� 5!      $ 
Horizontal=�6   $��5q�66   .+�5"      �� $��BaudRate��6    $��60��60   $
��Left=�6;   $��Center=�6V   �� 5#      $��80��6   ��5$      �� * SerialNotifiableModel.BaudList+ 5%      �� *SerialNotifiableModel.Baud+5&      �� 5(      $ 
Horizontal=�6   $��5q�66   .+�5)      �� $��Parity��6    $��60��6.   $
��Left=�69   $��Center=�6T   �� 5*      $��80��6   ��5+      �� *" SerialNotifiableModel.ParityList+ 5,      �� *SerialNotifiableModel.Parity+5-      �� 5/      $ 
Horizontal=�6   $��5q�66   .+�50      �� $��DataBits��6    $��60��60   $
��Left=�6;   $��Center=�6V   �� 51      $��80��6   ��52      �� *$"SerialNotifiableModel.DataBitsList+ 53      �� * SerialNotifiableModel.DataBits+54      �� 56      $ 
Horizontal=�6   $��5q�66   .+�57      �� $��StopBits��6    $��60��60   $
��Left=�6;   $��Center=�6V   �� 58      $��80��6   ��59      �� *$"SerialNotifiableModel.StopBitsList+ 5:      �� * SerialNotifiableModel.StopBits+5;      �� 5=      $ 
Horizontal=�6   $��5q�66   .+�5>      �� $��60��6    �� 5?      $��80��6   ��5@      �� *OpenCommand+��5A      �� *%#SerialNotifiableModel.SwitchContent+5B      5C      5D      �� 5F      $��Other��6   $	��165��6&   .��5G      �� .+�5H      �� $ 
Horizontal=�6!   $��5q�6:   .+�5I      �� $��HexRead��6$   $��60��63   $
��Left=�6>   $��Center=�6Y   �� 5J      $��80��6#   	 d� 	IsChecked	 6.   �� *SerialNotifiableModel.HexRead+5K      �� 5M      $ 
Horizontal=�6!   $��5q�6:   $	��Top=�6E   .+�5N      �� $��HexSend��6$   $��60��63   $
��Left=�6>   $��Center=�6Y   �� 5O      $��80��6#   	 6.   �� *SerialNotifiableModel.HexSend+5P      �� 5R      $ Vertical=�6!   $��5q�68   $
��Left=�6C   .+�5S      �� $	��100��6!   $��clear read area��6-   $��0,5,5,5q�6G   ��5T   !   �� *ClearReceivedCommand+�� 5U      $	��100��6!   $��clear send area��6-   $��0,5,5,5q�6G   ��5V   !   �� *ClearMsg2SendCommand+5W      �� 5Y      $ 
Horizontal=�6!   $��5q�6:   $
��Left=�6E   .+�5Z      �� $��定时发送��6#   ��5[   #   �� *SetTimedsendingCommand+	 5\   #   �� *#!SerialNotifiableModel.IsTimedSend+�� 5]      $��48��6"   $��5,0,0,0q�6-   ��6>   �� * SerialNotifiableModel.TimeSpan+�� 5^      $��ms��6$   $��5,0,0,0q�6.   5_      5`      5a      5b      �� 5d   
   $��	Read Aera��6   $��5q�6&   $��0��5e      $��1��6    .��5f      � .+�5g      �� 
������ ��5h      �� *&$SerialNotifiableModel.ReceivedString+5i      5j      �� 5m   
   $��
Write Aera��6   $��5q�6'   $��1��5n      $��1��6    .��5o      � .+�5p      �� 
������ ��5q      �� *#!SerialNotifiableModel.String2Send+�� 5s      $ 
Horizontal=�6   $��Bottom=�66   $��Right=�6Q   .+�5t      �� $
��send��6   $��5q�6,   $��40��67   $��20��6B   ��5u      �� *SendDataCommand+5v      5x      5y      5z      5{      