import javax.swing.*;
import javax.swing.text.DefaultEditorKit;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/**
 * Project originally from tutorial at http://forum.codecall.net/topic/49721-simple-text-editor/
 * Created by parker on 4/22/17.
 */
public class TextEditorPKT extends JFrame {
    private JTextArea area = new JTextArea(20,120);
    private JFileChooser dialog = new JFileChooser(System.getProperty("user.dir"));
    private String currentFile = "Untitled";
    private boolean changed = false;
    private KeyListener k1 = new KeyAdapter() {
        public void keyPressed(KeyEvent e){
            changed = true;
            Save.setEnabled(true);
            SaveAs.setEnabled(true);
        }
    };
    Action Open = new AbstractAction("Open", new ImageIcon(this.getClass().getResource("open.gif"))) {
        public void actionPerformed(ActionEvent e) {
            saveOld();
            if(dialog.showOpenDialog(null)==JFileChooser.APPROVE_OPTION){
                readInFile(dialog.getSelectedFile().getAbsolutePath());
            }
            SaveAs.setEnabled(true);
        }
    };
    Action Save = new AbstractAction("Save", new ImageIcon(this.getClass().getResource("save.gif"))) {
        public void actionPerformed(ActionEvent e) {
            if(!currentFile.equals("Untitled")){
                saveFile(currentFile);
            }
            else{
                saveFileAs();
            }
        }
    };
    Action SaveAs = new AbstractAction("Save as...") {
        public void actionPerformed(ActionEvent e) {
            saveFileAs();
        }
    };
    Action Quit = new AbstractAction("Quit") {
        public void actionPerformed(ActionEvent e) {
            saveOld();
            System.exit(0);
        }
    };
    ActionMap actionMap = area.getActionMap();
    Action Cut = actionMap.get(DefaultEditorKit.cutAction);
    Action Copy = actionMap.get(DefaultEditorKit.copyAction);
    Action Paste = actionMap.get(DefaultEditorKit.pasteAction);

    public TextEditorPKT(){
        area.setFont(new Font("Monospaced", Font.PLAIN, 12));
        JScrollPane scroll = new JScrollPane(area, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        add(scroll,BorderLayout.CENTER);

        JMenuBar menuBar = new JMenuBar();
        setJMenuBar(menuBar);
        JMenu file = new JMenu("File");
        JMenu edit = new JMenu("Edit");
        menuBar.add(file);
        menuBar.add(edit);


        //file.add(New);
        file.add(Open);
        file.add(Save);
        file.add(SaveAs);
        file.add(Quit);
        file.addSeparator();

        for(int i = 0; i < 4; i++){
            file.getItem(i).setIcon(null);
        }
        edit.add(Cut);
        edit.add(Copy);
        edit.add(Paste);
        edit.getItem(0).setText("Cut Out");
        edit.getItem(1).setText("Copy");
        edit.getItem(2).setText("Paste");

        JToolBar toolbar = new JToolBar();
        add(toolbar, BorderLayout.NORTH);
        //toolbar.add(New);
        toolbar.add(Open);
        toolbar.add(Save);
        toolbar.addSeparator();

        JButton cut = toolbar.add(Cut),
                copy = toolbar.add(Copy),
                paste = toolbar.add(Paste);

        cut.setText(null);
        cut.setIcon(new ImageIcon(this.getClass().getResource("cut.gif")));
        copy.setText(null);
        copy.setIcon(new ImageIcon(this.getClass().getResource("copy.gif")));
        paste.setText(null);
        paste.setIcon(new ImageIcon(this.getClass().getResource("paste.gif")));

        Save.setEnabled(false);
        SaveAs.setEnabled(false);

        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        pack();
        area.addKeyListener(k1);
        setTitle(currentFile);
        setVisible(true);
    }

    public static void main(String[] args){
        new TextEditorPKT();
    }

    private void saveFileAs(){
        //dialog.setDialogTitle("Save As");
        if(dialog.showSaveDialog(null)==JFileChooser.APPROVE_OPTION){
            saveFile(dialog.getSelectedFile().getAbsolutePath());
        }
    }

    private void saveOld(){
        if(changed){
            if(JOptionPane.showConfirmDialog(this, "Would you like to save " + currentFile + " ?", "Save", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION){
                saveFile(currentFile);
            }
        }
    }

    private void readInFile(String fileName){
        try {
            FileReader freader = new FileReader(fileName);
            area.read(freader, null);
            freader.close();
            currentFile = fileName;
            setTitle(currentFile);
            changed = false;
        }
        catch (IOException e){
            Toolkit.getDefaultToolkit().beep();
            JOptionPane.showMessageDialog(this, "Error, File not found: " + fileName);
        }
    }

    private void saveFile(String fileName){
        try {
            FileWriter fwriter = new FileWriter(fileName);
            area.write(fwriter);
            fwriter.close();
            currentFile = fileName;
            setTitle(currentFile);
            changed = false;
            Save.setEnabled(false);
        }
        catch (IOException e){

        }
    }
}
