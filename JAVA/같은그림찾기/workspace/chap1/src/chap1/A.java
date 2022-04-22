package chap1;
import java.awt.*;  
import java.awt.event.*;  
import javax.swing.*;  
import javax.swing.event.*;  
class A extends JFrame implements ActionListener{  
 Container con;  
 private ImageIcon before = new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\4.jpg");  
 private ImageIcon after = new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\3.jpg");  
 private JButton b1 = new JButton(before);  
 private JButton b2 = new JButton(after);;  
 A(){  
  init();  
  start();  
  setSize(500,500);  
  setVisible(true);  
 }  
 void init(){  
  b1.setIconTextGap(1);  
  b2.setIconTextGap(1);  
  con=this.getContentPane();  
  con.add("Center",b1);  
 }  
 void start(){  
  b1.addActionListener(this);  
  b2.addActionListener(this);  
       
 }  
 public void actionPerformed(ActionEvent e){  
  if((e.getSource()).equals(b1)){  
   con.removeAll();  
   con.add(b2);  
   b2.updateUI();  
  }  
  else{  
   con.removeAll();  
   con.add(b1);  
   b1.updateUI();  
  }  
 }  
 public static void main(String[] args) {  
  new A();  
 }  
} 