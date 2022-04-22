package chap1;

import java.awt.*;
import javax.swing.*;
import javax.swing.border.*;

public class ImagePaenl extends JPanel{
     Image image;
    
   public ImagePaenl(){
    image = new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\1.jpg").getImage();
    
  }
   
   public void paint(Graphics g){
	   g.drawImage(image, 0, 0, getWidth(), getHeight(), this);
	   
	   }
}
