library ieee;
use ieee.std_logic_1164.all;

entity alu32 is
  generic (
    bw : integer := 32
  );
  port (
    A : in std_logic_vector(bw - 1 downto 0);
    B : in std_logic_vector(bw - 1 downto 0);
    op : in std_logic_vector(3 downto 0);
    cout : out std_logic;
    zero : out std_logic;
    less : out std_logic;
    res : out std_logic_vector(bw - 1 downto 0);
    cin : inout std_logic;
    ofl : out std_logic
  );
end alu32;

architecture behavioral of alu32 is
  signal temp : std_logic_vector(bw - 1 downto 0);
begin
  case op is
    when "000" => -- Add
      temp := A + B;
    when "001" => -- Subtract
      temp := A - B;
    when "010" => -- AND
      temp := A and B;
    when "011" => -- OR
      temp := A or B;
   when others => -- Not implemented
      temp := (others => '0');
  end case;

  cout <= temp(31);
  zero <= temp(30);
  less <= temp(29);
  res <= temp(bw - 1 downto 0);
  ofl <= temp(bw);

  cin <= cin;
end behavioral;