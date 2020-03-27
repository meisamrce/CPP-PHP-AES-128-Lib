<?php
        function encrypt($key,$iv,$data)
        {
            $method = 'AES-128-CBC';
            $ivsize = openssl_cipher_iv_length($method);
            $en = openssl_encrypt($data,$method,$key,OPENSSL_RAW_DATA,$iv);
            return base64_encode($en);        
        }

        function decrypt($key,$iv,$data)
        {
            $method = 'AES-128-CBC';
            $data = base64_decode($data);
            $ivsize = openssl_cipher_iv_length($method);
            $data = openssl_decrypt($data
                    ,$method,$key,OPENSSL_RAW_DATA,$iv);
            return $data;       
        }        

		print encrypt('0123456789012345','0123456789012345','@dorsateam');
		print "\n";
		print decrypt('0123456789012345','0123456789012345','MROdbaxFiWmPtj3OvjWICA==');
?>