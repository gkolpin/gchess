#include "move.h"

#include <stdio.h>

int main(){
  move m = 23242;
  
  m = m_set_all(m, 7, 6, 5, 4, 3, 2);

  printf("%d %d %d %d %d %d\n", m_get_orow(m), m_get_ocol(m),
	 m_get_nrow(m), m_get_ncol(m), m_get_pp(m), m_get_cp(m));

  m = m_set_ocol(m, 1);

  printf("%d %d %d %d %d %d\n", m_get_orow(m), m_get_ocol(m),
	 m_get_nrow(m), m_get_ncol(m), m_get_pp(m), m_get_cp(m));
  
}
