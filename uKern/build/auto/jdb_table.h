// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef jdb_table_h
#define jdb_table_h

//
// INTERFACE definition follows 
//

#line 2 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_table.cpp"

class Jdb_table
{
public:
  enum
  {
    Nothing = 0,
    Handled,
    Redraw,
    Edit,
    Back,
    Exit,
  };
  
  virtual unsigned col_width(unsigned col) const = 0;
  virtual unsigned long cols() const = 0;
  virtual unsigned long rows() const = 0;
  virtual char col_sep(unsigned col) const;
  virtual void draw_entry(unsigned long row, unsigned long col) = 0;
  virtual unsigned key_pressed(int key, unsigned long &row, unsigned long &col);
  virtual void print_statline(unsigned long row, unsigned long col) = 0;
  virtual bool has_row_labels() const;
  virtual bool has_col_labels() const;
  virtual unsigned width() const;
  virtual unsigned height() const;

  virtual bool edit_entry(unsigned long row, unsigned long col, unsigned cx, unsigned cy);

public:  
#line 122 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_table.cpp"
  bool
  show(unsigned long crow, unsigned long ccol);
  
#line 344 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_table.cpp"
  void
  draw_table(unsigned long row, unsigned long col,
                        unsigned lines, unsigned columns);

private:  
#line 78 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_table.cpp"
  unsigned long
  vis_cols(unsigned long first_col, unsigned long *w);
  
#line 105 "/home/major/programmation/fiasco-2013060718/src/kernel/fiasco/src/jdb/jdb_table.cpp"
  unsigned
  col_ofs(unsigned long first_col, unsigned long col);
};

#endif // jdb_table_h
