package chap1;

import java.awt.*;

import javax.swing.*;

import java.awt.event.*;

public class  BackFrame extends JFrame implements ActionListener{
 Container content;
 ImagePaenl imgP;
 
 ImageIcon b = new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\4.jpg");  
 ImageIcon a = new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\3.jpg"); 
 
 
 
 JButton b1=new JButton(a);
 JButton b2=new JButton(a);
 JButton b3=new JButton(a);
 JButton b4=new JButton(a);
 JButton b5=new JButton(a);
 JButton b6=new JButton(a);
 JButton b7=new JButton(a);
 JButton b8=new JButton(a);
 JButton b9=new JButton(a);
 JButton b10=new JButton(a);
 JButton b11=new JButton(a);
 JButton b12=new JButton(a);
 JButton b13=new JButton(a);
 JButton b14=new JButton(a);
 JButton b15=new JButton(a);
 JButton b16=new JButton(a);
 JButton b17=new JButton(a);
 JButton b18=new JButton(a);
 JButton b19=new JButton(a);
 JButton b20=new JButton(a);
 JButton b21=new JButton(a);
 JButton b22=new JButton(a);
 JButton b23=new JButton(a);
 JButton b24=new JButton(a);
 
 
 /*Newjb b1= new Newjb();
 Newjb b2= new Newjb();
 Newjb b3= new Newjb();
 Newjb b4= new Newjb();
 Newjb b5= new Newjb();
 Newjb b6= new Newjb();*/
 
 
 
public BackFrame(String title){
   super(title);
   imgP = new ImagePaenl();
   content = getContentPane();     
   content.add(imgP, BorderLayout.CENTER);
   
   imgP.setLayout(new GridLayout(4,6));
   
   
   imgP.add(b1); 
   imgP.add(b2); 
   imgP.add(b3); 
   imgP.add(b4); 
   imgP.add(b5); 
   imgP.add(b6); 
   imgP.add(b7); 
   imgP.add(b8); 
   imgP.add(b9); 
   imgP.add(b10);
   imgP.add(b11); 
   imgP.add(b12); 
   imgP.add(b13); 
   imgP.add(b14); 
   imgP.add(b15); 
   imgP.add(b16); 
   imgP.add(b17); 
   imgP.add(b18); 
   imgP.add(b19); 
   imgP.add(b20);
   imgP.add(b21); 
   imgP.add(b22); 
   imgP.add(b23); 
   imgP.add(b24); 
   
   
   
   add(imgP);
   setSize(1000, 1000);
   setVisible(true);
 }
	

 
public void actionPerformed(ActionEvent e){  
	 
}
 public static void main(String[] args){
   BackFrame frame = new BackFrame("πË∞Ê≥÷±‚");
   frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
 }
}