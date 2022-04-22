package chap1;


import javax.imageio.ImageIO;
import javax.swing.*;

import java.awt.*;
import java.awt.event.*;  

import javax.swing.event.*; 




public class Game extends JPanel{
	Image bg;
	
	public Game(){
	bg=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\1.jpg").getImage();
	}
	
	public void paintcomponent(Graphics g){
		g.drawImage(bg, 0, 0, getWidth(), getHeight(), this);
	}
	
public static void main(String[] args){
		
		JFrame frame = new JFrame();
		Container content= frame.getContentPane();
		Game bg=new Game();
		
		content.add(bg,BorderLayout.CENTER);
		
		
		/*bg.setLayout(new GridLayout(3,3));
		
		JButton b1=new JButton();
		bg.add(b1);
		bg.add(b1);
		bg.add(b1);
		bg.add(b1);
		bg.add(b1);
		bg.add(b1);
		bg.add(b1);
		bg.add(b1);
		bg.add(b1);*/
		
		//frame.setSize(800, 900);
		frame.setPreferredSize(new Dimension(800,1000));
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();
		frame.setVisible(true);
		
		
		
		
	}
}

