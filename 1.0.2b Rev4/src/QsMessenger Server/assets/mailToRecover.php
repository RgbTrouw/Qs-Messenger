<?php

// Pear Mail Library

require_once "Mail.php";

$from = '<*ReplaceField*>';
$to = $argv[1];
$subject = 'Password Reset - QsMessenger ';
$body = "Hello,\n";
$body .= "  \n";
$body .= "Your QsMessenger password reset code is: \n";
$body .= "  \n";
$body .= $argv[2];
$body .= "  \n";
$body .= "  \n";
$body .= "Please use it to reset your password...\n";
$body .= "  \n";
$body .= "  \n";
$body .= "Kind Regards,  \n";
$body .= "The QsMessenger Team  \n";
$body .= "  \n";
$body .= "@ QsMessenger v1.0.2b Rev4 2026";


$headers = array(
    'From' => $from,
    'To' => $to,
    'Subject' => $subject
);

$smtp = Mail::factory('smtp', array(
        'host' => 'ssl://smtp.gmail.com',
        'port' => '465',
        'auth' => true,
        'username' => '*ReplaceField*',
        'password' => '*ReplaceField*'
    ));

$mail = $smtp->send($to, $headers, $body);

if (PEAR::isError($mail)) {
    echo('<p>' . $mail->getMessage() . '</p>');
} else {
    // echo("Password Recovery Mail Successfully Sent! \n");
}
?>
