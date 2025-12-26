// Pear Mail Library
<?php
require_once "Mail.php";

$from = '<*Replace*>';
$to = $argv[1];
$subject = 'QsMessenger at %Server% Account Registration';
$body = "Hello,\n";
$body .= "\n";
$body .= "Your QsMessenger activation code is: \n";
$body .= $argv[2];
$body .= "\n";

$body .= "Please use it to activate your account...\n";
$body .= "\n";
$body .= "\n";
$body .= "Kind Regards,\n";
$body .= "The QsMessenger at %Server% Team";


$headers = array(
    'From' => $from,
    'To' => $to,
    'Subject' => $subject
);

$smtp = Mail::factory('smtp', array(
        'host' => 'ssl://smtp.gmail.com',
        'port' => '465',
        'auth' => true,
        'username' => '*Replace*',
        'password' => '*Replace*'
    ));

$mail = $smtp->send($to, $headers, $body);

if (PEAR::isError($mail)) {
    echo('<p>' . $mail->getMessage() . '</p>');
} else {
    echo('<p>Message successfully sent!</p>');
}
?>
