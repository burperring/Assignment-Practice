package chap1;

import java.util.Random;

import javax.swing.ImageIcon;

public class Gameset {
	ImageIcon[] image;
	int [] arr;
	public Gameset() {
		// TODO Auto-generated constructor stub
		image=new ImageIcon[13];
		arr=new int[24];
	}
	public void imageFunction() {
		image[0]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\3.jpg");
		image[1]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\c1.jpg");
		image[2]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\c2.jpg");
		image[3]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\c3.jpg");
		image[4]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\c4.jpg");
		image[5]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\c5.jpg");
		image[6]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\c6.jpg");
		image[7]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\p1.jpg");
		image[8]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\p2.jpg");
		image[9]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\p3.jpg");
		image[10]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\p4.jpg");
		image[11]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\p5.jpg");
		image[12]=new ImageIcon("D:\\≈‰∑ª\\workspace\\chap1\\src\\chap1\\p6.jpg");
	}
	public void randNumber()
	{
		int check=0;
		Random rand=new Random();
		for(int i=0;i<arr.length;i++)
		{
			arr[i]=rand.nextInt(12)+1;
			for(int x=0;x<i;x++)
			{
				if(arr[i]==arr[x])
					check++;
			}
			if(check==2)
			{
				check=0;
				i--;
				continue;
			}
			
			check=0;
		}
	}
	public int GetArr(int i) {
		return arr[i];
	}
	public ImageIcon GetImage(int i) {
		return image[i];
	}
}